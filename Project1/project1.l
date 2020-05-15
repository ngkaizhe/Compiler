%{
#include "stdio.h" 
#include "project1.h"
int lineNumber = 0;
char lineBuffer[MAX] = {0};

// string buffer
char sBuffer[MAX] = {0};
char *sPointer;

// symbol table
struct SymbolTable* symbolTable;
%}

/* regex definitions*/
/* delimiter->comma(,) colon(:) period(.) semicolon(;) parentheses(()) square brackets([]) brackets({})*/
comma           [,]
colon           [:]
period          [.]
semicolon       [;]
parenthese      [()]
squarebracket   [[\]]
bracket         [{}]
/*arithmetic, relational, and logical operators*/
arithmetic      [\+\-*\/]
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
boolean         (true)|(false)
real            [0-9]+"."[0-9]+([Ee][+-]?[0-9]+)?

non-number-alphabet         [^a-zA-Z0-9]

/*string transition*/
%x STRING

/* token need to discard, whitespace and comments*/
/* comment transition*/
%x SINGLECOMMENT
%x MULTICOMMENT

/* symbol tables*/

%%
\"              {
    BEGIN STRING; 
    sPointer = sBuffer;
    addList(yytext);
}
<STRING>\"\"    {
    *sPointer++ = '\"';
    addList(yytext);
}
<STRING>\"      {
    BEGIN INITIAL;
    *sPointer = '\0';
    tokenType("String", sBuffer);
    addList(yytext);
}
<STRING>\n    {
    BEGIN INITIAL;
    fprintf(yyout, "Semantic error in line %d. Missing closing quote.\n", lineNumber+1);
    listLine();
}
<STRING>.       { *sPointer++ = *yytext; addList(yytext);}


\/\/            {
    BEGIN SINGLECOMMENT;
    addList(yytext);
}
<SINGLECOMMENT>\n    {
    BEGIN INITIAL;
    listLine();
}
<SINGLECOMMENT>.       { addList(yytext);}


\/\*            {
    BEGIN MULTICOMMENT;
    addList(yytext);
}
<MULTICOMMENT>\n    {
    listLine();
}
<MULTICOMMENT>\*\/    {
    BEGIN INITIAL;
    addList(yytext);
}
<MULTICOMMENT>.       { addList(yytext);}


{comma}           {tokenNonType(yytext);     addList(yytext);}
{colon}           {tokenNonType(yytext);     addList(yytext);}
{period}          {tokenNonType(yytext);     addList(yytext);}
{semicolon}       {tokenNonType(yytext);     addList(yytext);}
{parenthese}      {tokenNonType(yytext);     addList(yytext);}
{squarebracket}   {tokenNonType(yytext);     addList(yytext);}
{bracket}         {tokenNonType(yytext);     addList(yytext);}

{arithmetic}      {tokenOperator("Arithmetic operator", yytext);    addList(yytext);}
{remainder}       {tokenOperator("Arithmetic operator", yytext);     addList(yytext);}
{relational}      {tokenOperator("Relational operator", yytext);     addList(yytext);}
{logical}         {tokenOperator("Logical operator", yytext);        addList(yytext);}

{keyword}         {tokenKeyword(yytext);     addList(yytext);}
{typekeyword}     {tokenKeyword(yytext);     addList(yytext);}

{integer}         {tokenType("Integer constant", yytext);    addList(yytext);}
{boolean}         {tokenType("Boolean constant", yytext);    addList(yytext);}
{real}            {tokenType("Real constant", yytext);       addList(yytext);}

{identifier}      {tokenType("Id", yytext);      addList(yytext);   insert(symbolTable, yytext);}


[ \t\r]+          {addList(yytext);}
\n                {listLine();}
.                 {handleError("identifier", yytext);}

%%

int yywrap(void){
    // if the last line wasn't the newline, we need to manually output the lineBuffer
    if(lineBuffer[0]){
        listLine();
    }
    return 1;
}

