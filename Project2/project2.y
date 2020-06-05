%{
void yyerror(char* s);
int yylex();
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include "project2.h"

%}

%union{
    /* value part */
    int ival;
    double dval;
    char cval;
    string sval;

    /* value from id */
    string idName;
}

%start program
%token statement
%token exp

%token INTEGER DOUBLE CHAR STRING
%token VARIABLE
%token UMINUS

%type <ival> INTEGER
%type <dval> DOUBLE
%type <cval> CHAR
%type <sval> STRING

/* associativity of operators */
%right '='
%left '-' '+'
%left '*' '/'
%nonassoc UMINUS

%%
/* descriptions of expected inputs corresponding actions (in C)*/

program :   statement ';' {;}
        |   program statement ';' {;}
        ;

statement   : VARIABLE '=' exp {;}
            ;

exp     :   term        {$$ = $1;}
        |   exp '+' term {$$ = $1 + $3;}
        |   exp '-' term {$$ = $1 - $3;}
        |   exp '*' term {$$ = $1 * $3;}
        |   exp '/' term {$$ = $1 / $3;}
        |   '-' expr %prec UMINUS {$$ = $2 * -1;}
        ;

term    :   INTEGER     {$$ = $1;}
        |   DOUBLE      {$$ = $1;}
        |   CHAR        {$$ = $1;}
        |   STRING      {$$ = $1;}
        |   VARIABLE    {;}
        ;

%%

void yyerror(char* s){
    fprintf(stderr, "%s\n", s);
}