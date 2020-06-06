%{
#include "y.tab.hpp"
#include "project2.h"

extern int lineNumber = 0;
extern string lineBuffer = "";

// string buffer
extern string sBuffer = "";
%}

%option yylineno

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
assignment      [=]
/*keywords*/
keyword         (break)|(case)|(continue)|(def)|(do)|(else)|(exit)|(for)|(if)|(null)|(print)|(println)|(repeat)|(return)|(to)|(var)|(while)
typekeyword     (boolean)|(class)|(float)|(int)|(object)|(string)|(type)|(val)|(char)

/*identifiers*/
identifier      [a-zA-Z][A-za-z0-9]*
/*constants*/
integer         [0-9]+
real            [0-9]+"."[0-9]+([Ee][+-]?[0-9]+)?

true            true
false           false


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
    addList(yytext);
}
<STRING>\"\"    {
    sBuffer += "\"";
    addList(yytext);
}
<STRING>\"      {
    BEGIN INITIAL;
    addList(yytext);

    Value retValue;
    retValue.valueType = VALUETYPE::STRING;
    retValue.sval = string(yytext);

    yylval.value = new Value(retValue);
    return VALUETOKEN;
}
<STRING>\n    {
    BEGIN INITIAL;
    yyerror("Semantic error of string. Missing closing quote.\n");
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


{comma}             {addList(yytext);}
{colon}             {addList(yytext);}
{period}            {addList(yytext);}
{semicolon}         {addList(yytext);}
{parenthese}        {addList(yytext);}
{squarebracket}     {addList(yytext);}
{bracket}           {addList(yytext);}

{arithmetic}        {addList(yytext); return yytext[0];}
{remainder}         {addList(yytext); return yytext[0];}
{relational}        {addList(yytext);}
{logical}           {addList(yytext);}
{assignment}        {addList(yytext); return yytext[0];}

{keyword}           {addList(yytext);}
{typekeyword}       {addList(yytext);}

{integer}           {
                        addList(yytext);
                        Value retValue;
                        retValue.valueType = VALUETYPE::INT;
                        retValue.ival = stoi(string(yytext));
                        yylval.value = new Value(retValue);

                        return VALUETOKEN;
                    }

{true}              {
                        addList(yytext);
                        Value retValue;
                        retValue.valueType = VALUETYPE::BOOLEAN;
                        retValue.bval = true;
                        yylval.value = new Value(retValue);

                        return VALUETOKEN;
                    }
{false}             {
                        addList(yytext);
                        Value retValue;
                        retValue.valueType = VALUETYPE::BOOLEAN;
                        retValue.bval = false;
                        yylval.value = new Value(retValue);

                        return VALUETOKEN;
                    }

{real}              {
                        addList(yytext);
                        Value retValue;
                        retValue.valueType = VALUETYPE::FLOAT;
                        retValue.fval = stof(string(yytext));
                        yylval.value = new Value(retValue);

                        return VALUETOKEN;
                    }

{identifier}        {
                        addList(yytext);
                        yylval.idname = new string(yytext);
                        return ID_NAME;
                    }


[ \t\r]+            {addList(yytext);}
\n                  {listLine();}
.                   {yyerror("Unrecognized character detected!");}

%%

int yywrap(void){
    // if the last line wasn't the newline, we need to manually output the lineBuffer
    if(lineBuffer[0]){
        listLine();
    }
    return 1;
}

