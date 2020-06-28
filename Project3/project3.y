%{

#include "project3.h"
#include "stdio.h"

SymbolTable symbolTable = SymbolTable();

int yyerror(const char* s);
int yyparse();
int yylex();

extern int yylineno;  // defined and maintained in lex
extern FILE* yyin, *yyout;

// function name to dynamic tracking current function scope
ID* functionScopedPtr;
bool hasReturn;
/* function called check parameter index*/
ID* functionCalledPtr;
int parameterIndex;

// tab count
int tabCount = 0;
// print the tab count
void PrintJasmTab();


// init the label counter
vector<int> LabelManager::labelCounters = {0, 0, 0, 0, 0, 0, 0, 0, 0};
%}

// all union var should be as pointer(i think is memory allocation problems)
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
%token FOR_SET

%token OpenParenthese
%token CloseParenthese
%token OpenSquareBracket
%token CloseSquareBracket
%token OpenBracket
%token CloseBracket

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
PROGRAM     :   
            OBJECT ID_NAME 
            {
                DebugLog("Object definition start!");
                ID* objectIdPtr = new ID();
                objectIdPtr->IDName = *$2;
                objectIdPtr->idType = IDTYPE::OBJECTID;
                symbolTable.Insert(objectIdPtr);

                // start to output to the file
                PrintJasmTab();
                fprintf(yyout, "class %s\n", objectIdPtr->IDName.c_str());
            }   

            '{'
            {
                // create new scope
                symbolTable.CreateSymbol();

                // start to output to the file
                PrintJasmTab();
                fprintf(yyout, "{\n");
                tabCount++;
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

                // start to output to the file
                tabCount--;
                PrintJasmTab();
                fprintf(yyout, "}\n");
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
                            ID* functionIDPtr = new ID();
                            functionIDPtr->SetToFunction(*$2);

                            // set the functionScopedPtr to current function
                            functionScopedPtr = symbolTable.Insert(functionIDPtr);
                            hasReturn = false;
                        }

                        FUNCTION_DEFINITION2 '{'
                        {
                            // create the scope
                            symbolTable.CreateSymbol();

                            // put all parameter into the current function parameters scope
                            for(int i=0; i< functionScopedPtr->parameters.size(); i++){
                                symbolTable.Insert(functionScopedPtr->parameters[i]);
                            }

                            // start to output to the file
                            PrintJasmTab();
                            fprintf(yyout, "method public static %s %s(", 
                                functionScopedPtr->retVal.ValueTypeString().c_str(), functionScopedPtr->IDName.c_str());

                            // parameter parts
                            // main function
                            if(functionScopedPtr->IDName == "main"){
                                fprintf(yyout, "java.lang.String[]");
                            }
                            // normal function
                            else{
                                for(int i = 0; i<functionScopedPtr->parameters.size(); i++){
                                    fprintf(yyout, "%s", functionScopedPtr->parameters[i]->value.ValueTypeString().c_str());
                                    if(i != functionScopedPtr->parameters.size()-1)
                                        fprintf(yyout, ", ");
                                }
                            }

                            // close bracket
                            fprintf(yyout, ")\n");

                            PrintJasmTab();
                            fprintf(yyout, "max_stack 15\n");

                            PrintJasmTab();
                            fprintf(yyout, "max_locals 15\n");

                            PrintJasmTab();
                            fprintf(yyout, "{\n");
                            tabCount++;
                        }

                        STMTS '}'
                        {
                            // manually return
                            if(!hasReturn){
                                PrintJasmTab();
                                fprintf(yyout, "return\n");
                            }

                            // dump to check that we set the correct function
                            // functionScopedPtr->Dump();
                            // drop the current scope
                            symbolTable.DropSymbol();
                            // set the functionScopedPtr to null
                            functionScopedPtr = NULL;
                            hasReturn = false;

                            // start to output to the file
                            tabCount--;
                            PrintJasmTab();
                            fprintf(yyout, "}\n");
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
                            // set the return type for the function to void
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

                // set scope index (as this is the local variable)
                parameterID.scopeIndex = functionScopedPtr->parameters.size();

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

                // start to output to the file
                PrintJasmTab();
                // check return type
                // currently we only support int, char, boolean, float
                if(functionScopedPtr->retVal.valueType == VALUETYPE::BOOLEAN
                    || functionScopedPtr->retVal.valueType == VALUETYPE::INT
                    || functionScopedPtr->retVal.valueType == VALUETYPE::CHAR){
                    fprintf(yyout, "ireturn\n");
                }
                else if(functionScopedPtr->retVal.valueType == VALUETYPE::FLOAT){
                    fprintf(yyout, "freturn\n");
                }
                else{
                    yyerror("We only support return value type that is boolean, int, char, float, void!!!\n");
                }

                hasReturn = true;
            }
            | RETURN
            {
                // check whether we are in the function scope
                if(functionScopedPtr == NULL) 
                    yyerror("Return can only called inside the function scope!");

                // check whether the return exp's type is same as the current function type
                if(VALUETYPE::VOID != functionScopedPtr->retVal.valueType) 
                    yyerror("The function return type must be void!"); 
                
                // start to output to the file
                PrintJasmTab();
                fprintf(yyout, "return\n");

                hasReturn = true;
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
                    ID* lIDPtr = symbolTable.LookUp(*$1);
                    
                    // start to do the assignment operation
                    lIDPtr->SetValue(*$3);

                    // start to output
                    PrintJasmTab();

                    // if is global variable
                    if(symbolTable.isGlobalScope(*$1)){
                        fprintf(yyout, "%s\n", 
                            OperandStackManager::globalStore(lIDPtr, symbolTable.getObjectName()).c_str());
                    }
                    // else it must be local variable
                    else{
                        fprintf(yyout, "%s\n", 
                            OperandStackManager::localStore(lIDPtr).c_str());
                    }

                }
                |   ID_NAME '[' EXP ']' '=' EXP
                {
                    // id name must be valid
                    VALUE& arrID = symbolTable.LookUp(*$1)->value;

                    // 1st exp should only be int type
                    if($3->valueType != VALUETYPE::INT) yyerror("Array index must be integer type!");

                    // set value to the array content
                    arrID[$3->ival] = *$6;

                    // we dont support array assignment
                    yyerror("We don't support array assignment!\n");
                }
                | VALDECLARATION
                | VARDECLARATION
                | RETURN_STMT

                | PRINT 
                {
                    // start to output
                    PrintJasmTab();
                    fprintf(yyout, "getstatic java.io.PrintStream java.lang.System.out\n");
                }
                '(' EXP ')'
                {
                    DebugLog("Print function Called!");

                    // start to output
                    PrintJasmTab();
                    fprintf(yyout, "invokevirtual void java.io.PrintStream.print(%s)\n", $4->ValueTypeString().c_str());
                }

                | PRINTLN 
                {
                    // start to output
                    PrintJasmTab();
                    fprintf(yyout, "getstatic java.io.PrintStream java.lang.System.out\n");
                }
                '(' EXP ')'
                {
                    DebugLog("Println function Called!");

                    // start to output
                    PrintJasmTab();
                    fprintf(yyout, "invokevirtual void java.io.PrintStream.println(%s)\n", $4->ValueTypeString().c_str());
                }

                | READ ID_NAME
                {
                    DebugLog("Read function Called!");

                    yyerror("We dont support read function!\n");
                }

                | '{' 
                {
                    // symbolTable.CreateSymbol();

                    // // start to output
                    // PrintJasmTab();
                    // fprintf(yyout, "{\n");
                    // tabCount++;
                }
                STMTS '}'
                {
                    // symbolTable.DropSymbol();
                    // // start to output
                    // tabCount--;
                    // PrintJasmTab();
                    // fprintf(yyout, "}\n");
                }

                | IF_STMT

                | WHILE_STMT

                | FOR_STMT
                ;

// constant declaration
VALDECLARATION  :       VAL ID_NAME ':' VALUE_TYPE '=' VALUE_TOKEN
                        {
                            ID* newIdPtr = new ID();
                            newIdPtr->SetToConstVar(*$2);
                            // check ID is already used in this scope or not
                            // insert id with name to the symbol table
                            symbolTable.Insert(newIdPtr);

                            // check VALUE_TOKEN's value type same as VALUE_TYPE
                            newIdPtr->SetValueType(*$4);
                            newIdPtr->InitValue(*$6);
                        }
                |       VAL ID_NAME '=' VALUE_TOKEN
                        {
                            ID* newIdPtr = new ID();
                            newIdPtr->SetToConstVar(*$2);
                            // check ID is already used in this scope or not
                            // insert id with name to the symbol table
                            symbolTable.Insert(newIdPtr);
                            newIdPtr->InitValue(*$4);
                        }
                ;       

// variable declaration
VARDECLARATION  :       VAR ID_NAME ':' VALUE_TYPE 
                        {
                            ID* lIDPtr = new ID();
                            lIDPtr->SetToVar(*$2);
                            // check ID is already used in this scope or not
                            // insert id with name to the symbol table
                            symbolTable.Insert(lIDPtr);
                            // set value type
                            lIDPtr->SetValueType(*$4);

                            // start to output
                            // what we need to do
                            // 1. init variable

                            if(symbolTable.isGlobalScope(*$2)){
                                PrintJasmTab();
                                fprintf(yyout, "%s\n", 
                                    OperandStackManager::globalInit(lIDPtr, symbolTable.getObjectName()).c_str());
                            }
                            else{
                                // set the scope index of the local variable
                                lIDPtr->scopeIndex = symbolTable.validSymbols.back().ids.size() - 1;
                            }
                        }
                |       VAR ID_NAME '=' VALUE_TOKEN
                        {
                            ID* lIDPtr = new ID();
                            lIDPtr->SetToVar(*$2);
                            // check ID is already used in this scope or not
                            // insert id with name to the symbol table
                            symbolTable.Insert(lIDPtr);

                            // set value type
                            lIDPtr->InitValue(*$4);

                            // start to output
                            // what we need to do
                            // 1. init variable with value

                            // 1. init variable with value     
                            if(symbolTable.isGlobalScope(*$2)){
                                PrintJasmTab();
                                fprintf(yyout, "%s\n", 
                                    OperandStackManager::globalInitWithValue(lIDPtr, symbolTable.getObjectName()).c_str());
                            }
                            else{
                                // set the scope index of the local variable
                                lIDPtr->scopeIndex = symbolTable.validSymbols.back().ids.size() - 1;
                            }
                        }
                |       VAR ID_NAME ':' VALUE_TYPE '=' EXP
                        {
                            ID* lIDPtr = symbolTable.LookUp(*$2);

                            // check VALUE_TOKEN's value type same as VALUE_TYPE
                            lIDPtr->SetValueType(*$4);
                            lIDPtr->InitValue(*$6);
                            
                            // what we need to do
                            // 1. init variable with value

                            // 1. init variable with value
                            if(symbolTable.isGlobalScope(*$2)){
                                PrintJasmTab();
                                fprintf(yyout, "%s\n", 
                                    OperandStackManager::globalInitWithValue(lIDPtr, symbolTable.getObjectName()).c_str());
                            }
                            else{
                                // set the scope index of the local variable
                                lIDPtr->scopeIndex = symbolTable.validSymbols.back().ids.size() - 1;
                            }
                        }
                |       VAR ID_NAME ':' VALUE_TYPE '[' EXP ']'
                        {
                            ID* lIDPtr = symbolTable.LookUp(*$2);

                            // the value_token must be type int
                            if($6->valueType != VALUETYPE::INT) yyerror("array declaration's number value must be integer!");

                            // set the array range for id name
                            // and resize and the array length
                            lIDPtr->value = VALUE(*$4, $6->ival);

                            // we don't support array
                            yyerror("We don't support array declaration!\n");    
                        }       
                |       VAR ID_NAME
                        {
                            ID* lIDPtr = new ID();
                            lIDPtr->SetToVar(*$2);
                            // check ID is already used in this scope or not
                            // insert id with name to the symbol table
                            symbolTable.Insert(lIDPtr);
                            // we are going to set the var to default value... which is int
                            lIDPtr->SetValueType(VALUETYPE::INT);

                            // start to output
                            // what we need to do
                            // 1. init variable
                                        
                            if(symbolTable.isGlobalScope(*$2)){
                                PrintJasmTab();
                                fprintf(yyout, "%s\n", 
                                    OperandStackManager::globalInit(lIDPtr, symbolTable.getObjectName()).c_str());
                            }
                            else{
                                // set the scope index of the local variable
                                lIDPtr->scopeIndex = symbolTable.validSymbols.back().ids.size() - 1;
                            }
                        }
                ;
// expression
EXP     :   ID_NAME        
            {
                // find the id in the symbol table
                VALUE idVal = symbolTable.LookUp(*$1)->value;
                $$ = new VALUE(idVal);

                // this id name is right value
                // start to output
                ID* rIDPtr = symbolTable.LookUp(*$1);

                // check whether id is global or local or constant
                // is global
                if(rIDPtr->idType == IDTYPE::GLOBALVAR){
                    PrintJasmTab();
                    fprintf(yyout, "%s\n", 
                        OperandStackManager::globalLoad(rIDPtr, symbolTable.getObjectName()).c_str());
                }
                // else if local variable
                else if(rIDPtr->idType == IDTYPE::VARIABLE){
                    PrintJasmTab();
                    fprintf(yyout, "%s\n", 
                        OperandStackManager::localLoad(rIDPtr).c_str());
                }
                // else if constant
                else if(rIDPtr->idType == IDTYPE::CONSTVAR){
                    PrintJasmTab();
                    fprintf(yyout, "%s\n",
                        OperandStackManager::constantLoad(&idVal).c_str());
                }
                else{
                    yyerror("Rvalue can only be either constant, local var, global var!\n");
                }
            }
        |   EXP '+' EXP 
            {
                $$ = new VALUE(*$1 + *$3);
                // start to output
                // add operation only supports on float and int type
                PrintJasmTab();
                fprintf(yyout, "%s\n", LabelManager::getOperatorString(Operation::ADD, $1->valueType).c_str());
            }
        |   EXP '-' EXP 
            {
                $$ = new VALUE(*$1 - *$3);
                // start to output
                // sub operation only supports on float and int type
                PrintJasmTab();
                fprintf(yyout, "%s\n", LabelManager::getOperatorString(Operation::SUB, $1->valueType).c_str());
            }
        |   EXP '*' EXP 
            {
                $$ = new VALUE(*$1 * *$3);
                // start to output
                // mul operation only supports on float and int type
                PrintJasmTab();
                fprintf(yyout, "%s\n", LabelManager::getOperatorString(Operation::MUL, $1->valueType).c_str());
            }
        |   EXP '/' EXP 
            {
                $$ = new VALUE(*$1 / *$3);
                // start to output
                // div operation only supports on float and int type
                PrintJasmTab();
                fprintf(yyout, "%s\n", LabelManager::getOperatorString(Operation::DIV, $1->valueType).c_str());
            }

        |   '-' EXP %prec UMINUS {
                $$ = new VALUE(-(*$2));
                // start to output
                // unary negative operation only supports on float and int type
                PrintJasmTab();
                fprintf(yyout, "%s\n", LabelManager::getOperatorString(Operation::NEG, $2->valueType).c_str());
            }
        |   VALUE_TOKEN{
                $$ = $1;
                // start to output
                // this is constant expression
                PrintJasmTab();
                fprintf(yyout, "%s\n", OperandStackManager::constantLoad($1).c_str());
            }
        |   FUNCTION_CALLED

        |   NOT EXP{ 
                $$ = new VALUE(!(*$2));

                // start output
                PrintJasmTab();
                fprintf(yyout, "ixor\n");
            }
        |   EXP OR EXP { 
                $$ = new VALUE(*$1 || *$3);

                // start output
                PrintJasmTab();
                fprintf(yyout, "ior\n");
            }
        |   EXP AND EXP { 
                $$ = new VALUE(*$1 && *$3);

                // start output
                PrintJasmTab();
                fprintf(yyout, "iand\n");
            }

        |   EXP LT EXP  { 
                $$ = new VALUE(*$1 < *$3);

                // start output
                PrintJasmTab();
                fprintf(yyout, "%s\n", LabelManager::getOperatorString(Operation::SUB, $1->valueType).c_str());

                // change the value from float to int for comparison
                if($1->valueType == VALUETYPE::FLOAT){
                    PrintJasmTab();
                    fprintf(yyout, "d2i\n");
                }

                LabelManager::createComparisonLabel(LabelType::LLT);
            }
        |   EXP LE EXP  { 
                $$ = new VALUE(*$1 <= *$3);

                // start output
                PrintJasmTab();
                fprintf(yyout, "%s\n", LabelManager::getOperatorString(Operation::SUB, $1->valueType).c_str());

                // change the value from float to int for comparison
                if($1->valueType == VALUETYPE::FLOAT){
                    PrintJasmTab();
                    fprintf(yyout, "d2i\n");
                }

                LabelManager::createComparisonLabel(LabelType::LLE);
            }
        |   EXP EQ EXP  { 
                $$ = new VALUE(*$1 == *$3);

                // start output
                PrintJasmTab();
                fprintf(yyout, "%s\n", LabelManager::getOperatorString(Operation::SUB, $1->valueType).c_str());

                // change the value from float to int for comparison
                if($1->valueType == VALUETYPE::FLOAT){
                    PrintJasmTab();
                    fprintf(yyout, "d2i\n");
                }
                
                LabelManager::createComparisonLabel(LabelType::LEQ);
            }
        |   EXP NQ EXP  { 
                $$ = new VALUE(*$1 != *$3);

                // start output
                PrintJasmTab();
                fprintf(yyout, "%s\n", LabelManager::getOperatorString(Operation::SUB, $1->valueType).c_str());

                // change the value from float to int for comparison
                if($1->valueType == VALUETYPE::FLOAT){
                    PrintJasmTab();
                    fprintf(yyout, "d2i\n");
                }

                LabelManager::createComparisonLabel(LabelType::LNQ);
            }
        |   EXP GE EXP  { 
                $$ = new VALUE(*$1 >= *$3);

                // start output
                PrintJasmTab();
                fprintf(yyout, "%s\n", LabelManager::getOperatorString(Operation::SUB, $1->valueType).c_str());

                // change the value from float to int for comparison
                if($1->valueType == VALUETYPE::FLOAT){
                    PrintJasmTab();
                    fprintf(yyout, "d2i\n");
                }

                LabelManager::createComparisonLabel(LabelType::LGE);
            }
        |   EXP GT EXP  { 
                $$ = new VALUE(*$1 > *$3);

                // start output
                PrintJasmTab();
                fprintf(yyout, "%s\n", LabelManager::getOperatorString(Operation::SUB, $1->valueType).c_str());

                // change the value from float to int for comparison
                if($1->valueType == VALUETYPE::FLOAT){
                    PrintJasmTab();
                    fprintf(yyout, "d2i\n");
                }

                LabelManager::createComparisonLabel(LabelType::LGT);
            }
        ;

// function called to use
FUNCTION_CALLED         : ID_NAME 
                        {
                            // start to find the id name in the current scope
                            ID* functionIDPtr = symbolTable.LookUp(*$1);
                            // check the id type to be function
                            if(functionIDPtr->idType == IDTYPE::FUNCTION)
                                DebugLog("Function Called Detected. Function name is " + functionIDPtr->IDName + "......OK");
                            else    yyerror("ID Called wasn't function!");


                            // initialize function ptr
                            functionCalledPtr = functionIDPtr;
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
                            // check the value token value type against the function parameter index value type
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

// if else
IF_STMT                 : IF '(' EXP ')' 
                        {
                            // the exp must be boolean only
                            if($3->valueType != VALUETYPE::BOOLEAN) yyerror("If Statement only accept boolean expression!");
                            else    DebugLog("IF statement detected.......OK");

                            // start output
                            PrintJasmTab();
                            fprintf(yyout, "ifeq %s\n", LabelManager::getLabelString(LabelType::LIF, true).c_str());
                        } 
                        STMT 
                        {
                            // start output
                            PrintJasmTab();
                            fprintf(yyout, "goto %s\n", LabelManager::getLabelString(LabelType::LIF, false).c_str());

                            PrintJasmTab();
                            fprintf(yyout, "%s: \n", LabelManager::getLabelString(LabelType::LIF, true).c_str());
                        }
                        ELSE_STMT
                        {
                            // start output
                            PrintJasmTab();
                            fprintf(yyout, "%s: \n", LabelManager::getLabelString(LabelType::LIF, false).c_str());

                            LabelManager::updateCounter(LabelType::LIF);
                        }
                        ;

// else statement
ELSE_STMT               :   ELSE STMT
                        |
                        ;

// loops
// while loops
WHILE_STMT              : WHILE '(' EXP ')' 
                        {
                            // the exp must be boolean only
                            if($3->valueType != VALUETYPE::BOOLEAN) yyerror("While Statement only accept boolean expression!");
                            else    DebugLog("While statement detected.......OK");

                            
                        }
                        STMT
                        ;

// for loops
FOR_STMT                : FOR '(' ID_NAME FOR_SET EXP TO EXP ')' 
                        {
                            // both exp must be only int expression
                            if($5->valueType != VALUETYPE::INT){
                                yyerror("Assignment of for loop only can be int!");
                            }
                            if($7->valueType != VALUETYPE::INT){
                                yyerror("Terminate value of for loop only can be int!");
                            }

                            ID* forIDPtr = symbolTable.LookUp(*$3);
                            forIDPtr->value = *$5;
                        }
                        STMT
                        ;

%%
#include "lex.yy.cpp"

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

// print the tab count
void PrintJasmTab(){
    for(int i=0; i<tabCount; i++){
        fprintf(yyout, "\t");
    }
}