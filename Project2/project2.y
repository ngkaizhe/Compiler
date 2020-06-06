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
%}

%union{

    /* id name */
    string* idName;

    /* constant exp*/
    VALUE* value;
};

/* all name should be followed by T to indicate as token*/
%start STMTS


// token came from lex with value
%token <idName> ID_NAME
%token <value> VALUETOKEN

// token came from lex without value
%token INT_TYPE
%token FLOAT_TYPE
%token BOOL_TYPE
%token STRING_TYPE
%token CHAR_TYPE
%token VAR
%token VAL

%type <value> EXP

%token UMINUS

/* associativity of operators */
%right '='
%left '-' '+'
%left '*' '/'
%nonassoc UMINUS

%%

/* descriptions of expected inputs corresponding actions (in C)*/

STMTS   : STMT
        | STMT STMTS
        |
        ;

STMT    : ID_NAME '=' EXP {
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
        ;

EXP     :   ID_NAME        {
            // find the id in the symbol table
                VALUE idVal = symbolTable.LookUp(*$1).value;
                $$ = new VALUE(idVal);
            }
        |   EXP '+' EXP {$$ = new VALUE(oper('+', *$1, *$3));}
        |   EXP '-' EXP {$$ = new VALUE(oper('-', *$1, *$3));}
        |   EXP '*' EXP {$$ = new VALUE(oper('+', *$1, *$3));}
        |   EXP '/' EXP {$$ = new VALUE(oper('/', *$1, *$3));}
        |   '-' EXP %prec UMINUS {
                VALUE value;
                value.valueType = $2->valueType;
                if(value.valueType == VALUETYPE::INT) value.ival = -1;
                else if(value.valueType == VALUETYPE::FLOAT) value.fval = -1;
                else yyerror("Only float and int can do the unary operation!");

                $$ = new VALUE(oper('*', *$2, value));
            }
        |   VALUETOKEN
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
        VALUE answer;
        // set answer value type
        answer.valueType = VALUETYPE::FLOAT;
        // set answer value
        answer.fval = v1.fval + v2.fval;
        return answer;
    }
    // add operation for int
    if(operC == '+' && v1.valueType == VALUETYPE::INT){
        DebugLog("+ operator found!");
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
        VALUE answer;
        // set answer value type
        answer.valueType = VALUETYPE::FLOAT;
        // set answer value
        answer.fval = v1.fval - v2.fval;
        return answer;
    }
    // minus operation for int
    if(operC == '-' && v1.valueType == VALUETYPE::INT){
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
        VALUE answer;
        // set answer value type
        answer.valueType = VALUETYPE::FLOAT;
        // set answer value
        answer.fval = v1.fval * v2.fval;
        return answer;
    }
    // multiple operation for int
    if(operC == '*' && v1.valueType == VALUETYPE::INT){
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
        VALUE answer;
        // set answer value type
        answer.valueType = VALUETYPE::FLOAT;
        // set answer value
        answer.fval = v1.fval / v2.fval;
        return answer;
    }
    // divide operation for int
    if(operC == '/' && v1.valueType == VALUETYPE::INT){
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
    fprintf(stderr, "Error, Line%d: %s\n", yylineno, s);
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
        if(yyparse() == 1){
            yyerror("Parsing error! ");
        }

        fclose(yyin);
        fclose(yyout);
    }
    else if(yyin == NULL){
        printf("Input file not found!\n");
    }
    return 0;
}