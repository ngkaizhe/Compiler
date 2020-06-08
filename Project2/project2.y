%{
extern int yylex();

#include "project2.h"
#include "stdio.h"

// function declaration
VALUE oper(char operC, VALUE v1, VALUE v2);
SymbolTable symbolTable = SymbolTable();

int yyerror(const char* s);
extern int yylineno;  // defined and maintained in lex
extern int yyparse();
extern FILE* yyin, *yyout;

// function name to dynamic tracking current function scope
ID* functionScopedPtr;
/* function called check parameter index*/
ID* functionCalledPtr;
int parameterIndex;
%}

%union{

    /* id name */
    string* idName;

    /* constant exp*/
    VALUE* value;

    /* value type*/
    VALUETYPE* valueType;
};

/* all name should be followed by T to indicate as token*/
%start PROGRAM

// token came from lex with value
%token <idName> ID_NAME
%token <value> VALUE_TOKEN
%token <valueType> VALUE_TYPE

// token came from lex without value
%token VAR
%token VAL
%token DEF
%token IF
%token ELSE
%token FOR
%token PRINT
%token PRINTLN
%token READ
%token RETURN
%token TO
%token WHILE
%token OBJECT

%token AND
%token OR
%token NOT

%token LT
%token LE
%token EQ
%token NQ
%token GE
%token GT

%type <value> EXP
%type <value> FUNCTION_CALLED

%token UMINUS

/* associativity of operators */
%right '='
%left OR
%left AND
%left NOT
%left LT LE EQ GT GE NQ
%left '-' '+'
%left '*' '/'
%nonassoc UMINUS

%%

/* descriptions of expected inputs corresponding actions (in C)*/

// starting program token
PROGRAM     :   OBJECT ID_NAME 
            {
                DebugLog("Object definition start!");
                ID objectId = ID();
                objectId.IDName = *$2;
                objectId.idType = IDTYPE::OBJECTID;
                symbolTable.Insert(objectId);
            }   
                '{'
            {
                // create new scope
                symbolTable.CreateSymbol();
            }
                OBJCONTENT '}'
            {
                // check whether their are main function inside
                try{
                    symbolTable.LookUp("main");
                }
                catch(string s){
                    yyerror("The object content must have the main function!");
                }

                // drop the symbol table
                symbolTable.DropSymbol();
                DebugLog("Object definition end!");
            }
            ;

// obj content
OBJCONTENT : STMTS FUNCTION_DEFINITIONS;

// function definitions
FUNCTION_DEFINITIONS    : FUNCTION_DEFINITION FUNCTION_DEFINITIONS
                        | FUNCTION_DEFINITION
                        ;

// function definition
FUNCTION_DEFINITION :   DEF ID_NAME 
                        {
                            // insert function name
                            ID functionID = ID();
                            functionID.SetToFunction(*$2);

                            ID& functionRef = symbolTable.Insert(functionID);
                            // set the functionScopedPtr to current function
                            functionScopedPtr = &functionRef;
                        }
                        FUNCTION_DEFINITION2
                        '{'
                        {
                            // create the scope
                            symbolTable.CreateSymbol();

                            // put all parameter into the current scope
                            for(int i=0; i< functionScopedPtr->parameters.size(); i++){
                                symbolTable.Insert(*(functionScopedPtr->parameters[i]));
                            }
                        }
                        STMTS
                        '}'
                        {
                            // dump to check that we set the correct function
                            // functionScopedPtr->Dump();
                            // drop the current scope
                            symbolTable.DropSymbol();
                            // set the functionScopedPtr to null
                            functionScopedPtr = NULL;
                        }
                        ;

// second part of function definition (<formal_args>) <: type>
FUNCTION_DEFINITION2    : '(' FORMAL_ARGS ')' ':' VALUE_TYPE
                        {
                            // set the return type for the function
                            functionScopedPtr->SetReturnType(*$5);
                        }
                        | '(' FORMAL_ARGS ')'
                        {
                            // set the return type for the function
                            functionScopedPtr->SetReturnType(VALUETYPE::VOID);
                        }
                        ;

// insert all parameter into the current scope
FORMAL_ARGS : ARG ',' FORMAL_ARGS
            | ARG
            ;

ARG         : ID_NAME ':' VALUE_TYPE
            {
                // recreate a new ID as the function parameter
                ID parameterID = ID();
                parameterID.SetToVar(*$1);
                // set the value type too
                parameterID.SetValueType(*$3);

                // set the parameter to the function id
                functionScopedPtr->AddParameter(parameterID);
            }
            |
            ;

// return statement
RETURN_STMT : RETURN EXP
            {
                // check whether we are in the function scope
                if(functionScopedPtr == NULL) 
                    yyerror("Return can only called inside the function scope!");

                // check whether the return exp's type is same as the current function type
                if($2->valueType != functionScopedPtr->retVal.valueType) 
                    yyerror("The function return type definition is different as the function return type declaration!"); 
            }
            | RETURN
            {
                // check whether we are in the function scope
                if(functionScopedPtr == NULL) 
                    yyerror("Return can only called inside the function scope!");

                // check whether the return exp's type is same as the current function type
                if(VALUETYPE::VOID != functionScopedPtr->retVal.valueType) 
                    yyerror("The function return type is void!"); 
            }
            ;

// statements
STMTS   : STMT
        | STMT STMTS
        |
        ;

// statement
STMT            : ID_NAME '=' EXP 
                {
                    // check whether the exp has the same value type with the id name
                    VALUE rvalue = symbolTable.LookUp(*$1).value;
                    if(rvalue.valueType == $3->valueType){
                        DebugLog("Assignment operation done!");
                    }
                    else{
                        yyerror("Different type of value can't do the assignment operation!");
                    }
                }
                | EXP
                | VALDECLARATION
                | VARDECLARATION
                | RETURN_STMT
                | PRINT '(' EXP ')'
                {
                    DebugLog("Print function Called!");
                }
                | PRINTLN '(' EXP ')'
                {
                    DebugLog("Println function Called!");
                }
                | READ ID_NAME
                {
                    DebugLog("Read function Called!");
                }
                ;

// constant declaration
VALDECLARATION  :       VAL ID_NAME ':' VALUE_TYPE '=' VALUE_TOKEN
                        {
                            // error checking first
                            try{
                                ID newId = ID();
                                newId.SetToConstVar(*$2);
                                // check ID is already used in this scope or not
                                // insert id with name to the symbol table
                                ID& idRef = symbolTable.Insert(newId);

                                // check VALUE_TOKEN's value type same as VALUE_TYPE
                                idRef.SetValueType(*$4);
                                idRef.InitValue(*$6);
                            }
                            catch(string s){
                                yyerror(s.c_str());
                            }
                        }
                |       VAL ID_NAME '=' VALUE_TOKEN
                        {
                            // error checking first
                            try{
                                ID newId = ID();
                                newId.SetToConstVar(*$2);
                                // check ID is already used in this scope or not
                                // insert id with name to the symbol table
                                ID& idRef = symbolTable.Insert(newId);
                                idRef.InitValue(*$4);
                            }
                            catch(string s){
                                yyerror(s.c_str());
                            }
                        }
                ;       

// variable declaration
VARDECLARATION  :       VAR ID_NAME ':' VALUE_TYPE 
                        {
                            // error checking first
                            try{
                                ID newId = ID();
                                newId.SetToVar(*$2);
                                // check ID is already used in this scope or not
                                // insert id with name to the symbol table
                                ID& idRef = symbolTable.Insert(newId);

                                // set value type
                                idRef.SetValueType(*$4);
                            }
                            catch(string s){
                                yyerror(s.c_str());
                            }
                            
                        }
                |       VAR ID_NAME '=' VALUE_TOKEN
                        {
                            // error checking first
                            try{
                                ID newId = ID();
                                newId.SetToVar(*$2);
                                // check ID is already used in this scope or not
                                // insert id with name to the symbol table
                                ID& idRef = symbolTable.Insert(newId);

                                // set type
                                idRef.InitValue(*$4);
                            }
                            catch(string s){
                                yyerror(s.c_str());
                            }
                        }
                
                |       VAR ID_NAME ':' VALUE_TYPE '=' VALUE_TOKEN
                        {
                            // error checking first
                            try{
                                ID newId = ID();
                                newId.SetToVar(*$2);
                                // check ID is already used in this scope or not
                                // insert id with name to the symbol table
                                ID& idRef = symbolTable.Insert(newId);

                                // check VALUE_TOKEN's value type same as VALUE_TYPE
                                idRef.SetValueType(*$4);
                                idRef.InitValue(*$6);
                            }
                            catch(string s){
                                yyerror(s.c_str());
                            }
                        }
                |       VAR ID_NAME
                        {
                            // error checking first
                            try{
                                ID newId = ID();
                                newId.SetToVar(*$2);

                                // check ID is already used in this scope or not
                                // insert id with name to the symbol table
                                ID& idRef = symbolTable.Insert(newId);
                            }
                            catch(string s){
                                yyerror(s.c_str());
                            }
                        }
                |       VAR ID_NAME ':' VALUE_TYPE '[' EXP ']'
                        {
                            
                            // error checking first
                            try{
                                ID newId = ID();
                                newId.SetToVar(*$2);
                                
                                // check ID is already used in this scope or not
                                // insert id with name to the symbol table
                                ID* idRef = &symbolTable.Insert(newId);

                                // the value_token must be type int
                                if($6->valueType != VALUETYPE::INT) yyerror("array declaration's number value must be integer!");
                                // set the array range for id name
                                // and resize
                                idRef->value = VALUE(*$4, $6->ival);
                            }
                            catch(string s){
                                yyerror(s.c_str());
                            }
                        }
                ;     

// expression
EXP     :   ID_NAME        {
            // find the id in the symbol table
                VALUE& idVal = symbolTable.LookUp(*$1).value;
                $$ = new VALUE(idVal);
            }

        |   ID_NAME '[' EXP ']' '=' EXP
        {
            // id name must be valid
            VALUE& arrID = symbolTable.LookUp(*$1).value;

            // 1st exp should only be int type
            if($3->valueType != VALUETYPE::INT) yyerror("Array index must be integer type!");

            // set value to the array content
            arrID[$3->ival] = *$6;

        }
        |   EXP '+' EXP {$$ = new VALUE(*$1 + *$3);}
        |   EXP '-' EXP {$$ = new VALUE(*$1 - *$3);}
        |   EXP '*' EXP {$$ = new VALUE(*$1 * *$3);}
        |   EXP '/' EXP {$$ = new VALUE(*$1 / *$3);}

        |   '-' EXP %prec UMINUS {
                $$ = new VALUE(-(*$2));
            }
        |   VALUE_TOKEN
        |   FUNCTION_CALLED

        |   NOT EXP     { $$ = new VALUE(!(*$2));}
        |   EXP OR EXP { $$ = new VALUE(*$1 || *$3);}
        |   EXP AND EXP { $$ = new VALUE(*$1 && *$3);}
        |   EXP LT EXP  { $$ = new VALUE(*$1 < *$3);}
        |   EXP LE EXP  { $$ = new VALUE(*$1 <= *$3);}
        |   EXP EQ EXP  { $$ = new VALUE(*$1 == *$3);}
        |   EXP NQ EXP  { $$ = new VALUE(*$1 != *$3);}
        |   EXP GE EXP  { $$ = new VALUE(*$1 >= *$3);}
        |   EXP GT EXP  { $$ = new VALUE(*$1 > *$3);}
        ;

// function called to use
FUNCTION_CALLED         : ID_NAME 
                        {
                            // start to find the id name in the current scope
                            ID& functionID = symbolTable.LookUp(*$1);
                            // check the id type to be function
                            if(functionID.idType == IDTYPE::FUNCTION)
                                DebugLog("Function Called Detected. Function name is " + functionID.IDName + "......OK");
                            else    yyerror("ID Called wasn't function!");

                            // initialize function ptr
                            functionCalledPtr = &functionID;

                            // initialize function parameter index
                            parameterIndex = 0;
                        }
                        '(' FUNCTION_CALLED_ARGS ')' 
                        {   
                            // set the function return value to $$, to get change to exp
                            $$ = new VALUE(functionCalledPtr->retVal);
                            
                            // finish checking all function parameter, reset the parameter index and function pointer
                            parameterIndex = 0;
                            functionCalledPtr = NULL;
                        }
                        ;

// function called arguments
FUNCTION_CALLED_ARGS    : FUNCTION_CALLED_ARG ',' FUNCTION_CALLED_ARGS
                        | FUNCTION_CALLED_ARG
                        ;

// function called argument
FUNCTION_CALLED_ARG     : EXP
                        {
                            // check the value token value type against the function paramter index value type
                            if($1->valueType != functionCalledPtr->parameters[parameterIndex]->value.valueType){
                                yyerror(("Function called parameter " + to_string(parameterIndex) + ", doesn't have the correct value type!").c_str());
                            }
                            else{
                                DebugLog("Function called parameter " + to_string(parameterIndex) + ", Checked......OK");
                            }
                            // finish checking, add paramterIndex
                            parameterIndex++;
                        }
                        |
                        ;


%%
#include "lex.yy.cpp"

VALUE oper(char operC, VALUE v1, VALUE v2){
    // type should be the same
    if(v1.valueType != v2.valueType){
        yyerror("Different type the value cant do mathematics operation!");
    }

    // only float and int can do the operation
    if(v1.valueType != VALUETYPE::FLOAT && v1.valueType != VALUETYPE::INT){
        yyerror("Only float and int can do the mathematics operation!");
    }

    // add operation
    // add operation for float
    if(operC == '+' && v1.valueType == VALUETYPE::FLOAT){
        DebugLog("+ operator found! Checking Result......OK");
        VALUE answer;
        // set answer value type
        answer.valueType = VALUETYPE::FLOAT;
        // set answer value
        answer.fval = v1.fval + v2.fval;
        return answer;
    }
    // add operation for int
    if(operC == '+' && v1.valueType == VALUETYPE::INT){
        DebugLog("+ operator found! Checking Result......OK");
        VALUE answer;
        // set answer value type
        answer.valueType = VALUETYPE::INT;
        // set answer value
        answer.ival = v1.ival + v2.ival;
        return answer;
    }

    // minus operation
    // minus operation for float
    if(operC == '-' && v1.valueType == VALUETYPE::FLOAT){
        DebugLog("- operator found! Checking Result......OK");
        VALUE answer;
        // set answer value type
        answer.valueType = VALUETYPE::FLOAT;
        // set answer value
        answer.fval = v1.fval - v2.fval;
        return answer;
    }
    // minus operation for int
    if(operC == '-' && v1.valueType == VALUETYPE::INT){
        DebugLog("- operator found! Checking Result......OK");
        VALUE answer;
        // set answer value type
        answer.valueType = VALUETYPE::INT;
        // set answer value
        answer.ival = v1.ival - v2.ival;
        return answer;
    }

    // multiple operation
    // multiple operation for float
    if(operC == '*' && v1.valueType == VALUETYPE::FLOAT){
        DebugLog("* operator found! Checking Result......OK");
        VALUE answer;
        // set answer value type
        answer.valueType = VALUETYPE::FLOAT;
        // set answer value
        answer.fval = v1.fval * v2.fval;
        return answer;
    }
    // multiple operation for int
    if(operC == '*' && v1.valueType == VALUETYPE::INT){
        DebugLog("* operator found! Checking Result......OK");
        VALUE answer;
        // set answer value type
        answer.valueType = VALUETYPE::INT;
        // set answer value
        answer.ival = v1.ival / v2.ival;
        return answer;
    }

    // divide operation
    // divide operation for float
    if(operC == '/' && v1.valueType == VALUETYPE::FLOAT){
        DebugLog("/ operator found! Checking Result......OK");
        VALUE answer;
        // set answer value type
        answer.valueType = VALUETYPE::FLOAT;
        // set answer value
        answer.fval = v1.fval / v2.fval;
        return answer;
    }
    // divide operation for int
    if(operC == '/' && v1.valueType == VALUETYPE::INT){
        DebugLog("/ operator found! Checking Result......OK");
        VALUE answer;
        // set answer value type
        answer.valueType = VALUETYPE::INT;
        // set answer value
        answer.ival = v1.ival / v2.ival;
        return answer;
    }

    // shoudn't run till here
    yyerror("Invalid operation character passed!");
    return VALUE();
}

int yyerror(const char* s){
    // fprintf(stderr, "Error, Line%d: %s\n", yylineno, s);
    DebugLog("Error Message: " + string(s));
    exit(1);
}

// the main function to execute
int main(int argc, char* argv[]) {
    // set input and output file
    yyin = fopen(argv[1], "r");
    yyout = fopen(argv[2], "w");
    // init symbol table
    symbolTable.CreateSymbol();

    if(yyin != NULL){
        // perform parsing
        // error parsing
        try{
            if(yyparse() == 1)
            {
                yyerror("Parsing error! ");
            }
        }
        catch(string s){
            yyerror(s.c_str());
        } 
        

        fclose(yyin);
        fclose(yyout);
    }
    else if(yyin == NULL){
        printf("Input file not found!\n");
    }
    return 0;
}