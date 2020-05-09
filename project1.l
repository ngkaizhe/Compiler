%{
#include "stdio.h" 
#include "project1.h"
%}

/* regex definitions*/
/* delimiter->comma(,) colon(:) period(.) semicolon(;) parentheses(()) square brackets([]) brackets({})*/
comma           [,]
colon           [:]
period          [.]
semicolon       [;]
parenthese      [(]
squarebracket   [[\]]
bracket         [{}]
/*arithmetic, relational, and logical operators*/
arithmetic      [+\-*\/]
remainder       [%]
relational      [<>](=)?|[=!]=
logical         (&&)|(\|\|)|(!)
/*keywords*/
keyword         (break)|(case)|(continue)|(def)|(do)|(else)|(exit)|(for)|(if)|(null)|(print)|(println)|(repeat)|(return)|(to)|(var)|(while)
typekeyword     (boolean)|(class)|(float)|(int)|(object)|(string)|(type)|(val)|(char)
/*identifiers*/
identifier      [a-zA-z][0-9a-zA-Z_]*
/*constants*/
integer         [0-9]+
decimal         [0-9]*\.[0-9]+
boolean         (true)|(false)
real            ([+-]?[0-9]*\.[0-9]+)|([+-]?[0-9]+)
/*use state transition for string constant*/
string          (\").+(\")

/* token need to discard, whitespace and comments*/
/* symbol tables*/

%%
{real}          tokenNonType(yytext);
{string}        printf("string detected!\n%s\n", yytext);
\n              ;
.*              ;

%%

int yywrap(void){
    return 1;
}

