%{
#include "stdio.h" 
#include "project1.h"
int lineNumber = 0;
char lineBuffer[MAX] = {0};
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
identifier      [a-zA-Z][A-za-z0-9]*
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
{comma}           tokenNonType(yytext);
{colon}           tokenNonType(yytext);
{period}          tokenNonType(yytext);
{semicolon}       tokenNonType(yytext);
{parenthese}      tokenNonType(yytext);
{squarebracket}   tokenNonType(yytext);
{bracket}         tokenNonType(yytext);

{arithmetic}      tokenOperator("Arithmetic operator", yytext);
{remainder}       tokenOperator("Arithmetic operator", yytext);
{relational}      tokenOperator("Relational operator", yytext);
{logical}         tokenOperator("Logical operator", yytext);

{keyword}         tokenKeyword(yytext);
{typekeyword}     tokenKeyword(yytext);

{integer}         tokenType("Integer constant", yytext);
{decimal}         tokenType("Decimal constant", yytext);
{boolean}         tokenType("Boolean constant", yytext);
{real}            tokenType("Real constant", yytext);
{string}          printf("do something noob");

{identifier}      tokenType("Id", yytext);

[ \t\r]+          addList(yytext);
\n                listLine();

.                 handleError(yytext);

%%

int yywrap(void){
    // if the last line wasn't the newline, we need to manually output the lineBuffer
    if(lineBuffer[0]){
        listLine();
    }
    return 1;
}

