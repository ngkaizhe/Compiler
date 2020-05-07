%{
#include "stdio.h" 
#include "project1.h"
%}

/* regex definitions*/
digits      [0-9]+
/* delimiter->comma(,) colon(:) period(.) semicolon(;) parentheses(()) square brackets([]) brackets({})*/
comma           [,]
colon           [:]
period          [.]
semicolon       [;]
parenthese      [()]
squarebracket   [[\]]
bracket         [{}]

%%
{digits}        token(yytext);
\n              printf("newline found!\n");

%%

int yywrap(void){
    return 1;
}

