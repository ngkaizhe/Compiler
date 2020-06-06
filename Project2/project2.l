%{
    extern "C"
    {
        int yylex(void);
    }
#include "project2.h"

extern int lineNumber = 0;
extern string lineBuffer = "";

// string buffer
extern string sBuffer = "";
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
    AddList(yytext);
}
<STRING>\"\"    {
    sBuffer += "\"";
    AddList(yytext);
}
<STRING>\"      {
    BEGIN INITIAL;
    AddList(yytext);

    VALUE retValue;
    retValue.valueType = VALUETYPE::STRING;
    retValue.sval = string(yytext);

    yylval.value = new VALUE(retValue);
    return VALUETOKEN;
}
<STRING>\n    {
    BEGIN INITIAL;
    yyerror("Semantic error of string. Missing closing quote.\n");
    ListLine();
}
<STRING>.       { *sPointer++ = *yytext; AddList(yytext);}


\/\/            {
    BEGIN SINGLECOMMENT;
    AddList(yytext);
}
<SINGLECOMMENT>\n    {
    BEGIN INITIAL;
    ListLine();
}
<SINGLECOMMENT>.       { AddList(yytext);}


\/\*            {
    BEGIN MULTICOMMENT;
    AddList(yytext);
}
<MULTICOMMENT>\n    {
    ListLine();
}
<MULTICOMMENT>\*\/    {
    BEGIN INITIAL;
    AddList(yytext);
}
<MULTICOMMENT>.       { AddList(yytext);}


{comma}             {AddList(yytext);}
{colon}             {AddList(yytext);}
{period}            {AddList(yytext);}
{semicolon}         {AddList(yytext);}
{parenthese}        {AddList(yytext);}
{squarebracket}     {AddList(yytext);}
{bracket}           {AddList(yytext);}

{arithmetic}        {AddList(yytext); return yytext[0];}
{remainder}         {AddList(yytext); return yytext[0];}
{relational}        {AddList(yytext);}
{logical}           {AddList(yytext);}
{assignment}        {AddList(yytext); return yytext[0];}

{keyword}           {AddList(yytext);}
{typekeyword}       {AddList(yytext);}

{integer}           {
                        AddList(yytext);
                        VALUE retValue;
                        retValue.valueType = VALUETYPE::INT;
                        retValue.ival = stoi(string(yytext));
                        yylval.value = new VALUE(retValue);

                        return VALUETOKEN;
                    }

{true}              {
                        AddList(yytext);
                        VALUE retValue;
                        retValue.valueType = VALUETYPE::BOOLEAN;
                        retValue.bval = true;
                        yylval.value = new VALUE(retValue);

                        return VALUETOKEN;
                    }
{false}             {
                        AddList(yytext);
                        VALUE retValue;
                        retValue.valueType = VALUETYPE::BOOLEAN;
                        retValue.bval = false;
                        yylval.value = new VALUE(retValue);

                        return VALUETOKEN;
                    }

{real}              {
                        AddList(yytext);
                        VALUE retValue;
                        retValue.valueType = VALUETYPE::FLOAT;
                        retValue.fval = stof(string(yytext));
                        yylval.value = new VALUE(retValue);

                        return VALUETOKEN;
                    }

{identifier}        {
                        AddList(yytext);
                        yylval.idname = new string(yytext);
                        return ID_NAME;
                    }


[ \t\r]+            {AddList(yytext);}
\n                  {ListLine();}
.                   {yyerror("Unrecognized character detected!");}

%%

int yywrap(void){
    // if the last line wasn't the newline, we need to manually output the lineBuffer
    if(lineBuffer[0]){
        ListLine();
    }
    return 1;
}

