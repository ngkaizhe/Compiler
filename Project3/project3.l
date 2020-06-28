%{
#include "project3.h"

string lineBuffer = "";
// string buffer
string sBuffer = "";
%}

/* regex definitions*/
/* delimiter->comma(,) colon(:) period(.) semicolon(;) parentheses(()) square brackets([]) brackets({})*/
comma           [,]
colon           [:]
period          [.]
semicolon       [;]
parenthese      [()]
squarebracket   [\[\]]
bracket         [{}]

/*arithmetic operators*/
arithmetic      [\+\-*\/]

/*identifiers*/
identifier      [a-zA-Z][A-Za-z0-9]*
/*constants*/
integer         [0-9]+
real            [0-9]+"."[0-9]+([Ee][+-]?[0-9]+)?
char            '([^'\\\n]|\\.)'


/*string transition*/
%x STRINGS

/* token need to discard, whitespace and comments*/
/* comment transition*/
%x SINGLECOMMENT
%x MULTICOMMENT

/* symbol tables*/

%%
\"              {
    BEGIN STRINGS;
    AddList(yytext);
}
<STRINGS>\"\"    {
    sBuffer += "\"";
    AddList(yytext);
}
<STRINGS>\"      {
    BEGIN INITIAL;
    AddList(yytext);
    yylval.value = new VALUE(sBuffer);
    
    sBuffer = "";

    return VALUE_TOKEN;
}
<STRINGS>\n    {
    BEGIN INITIAL;
    yyerror("Semantic error of string. Missing closing quote.\n");
    ListLine();
}
<STRINGS>.       { sBuffer += string(yytext); AddList(yytext);}


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


"<-"                {AddList(yytext); return FOR_SET;}

{comma}             {AddList(yytext); return yytext[0];}
{colon}             {AddList(yytext); return yytext[0];}
{period}            {AddList(yytext); return yytext[0];}
{semicolon}         {AddList(yytext); return yytext[0];}
{parenthese}        {AddList(yytext); return yytext[0];}
{squarebracket}     {AddList(yytext); return yytext[0];}
{bracket}           {AddList(yytext); return yytext[0];}

{arithmetic}        {AddList(yytext); return yytext[0];}

"<="                 {AddList(yytext); return LE;}
"<"                   {AddList(yytext); return LT;}
"=="                  {AddList(yytext); return EQ;}
"!="                  {AddList(yytext); return NQ;}
">="                  {AddList(yytext); return GE;}
">"                  {AddList(yytext); return GT;}

"||"                  {AddList(yytext); return OR;}
"&&"                  {AddList(yytext); return AND;}
"!"                   {AddList(yytext); return NOT;}

"="                   {AddList(yytext); return yytext[0];}


"def"                 { AddList(yytext); return DEF;}

"if"                  { AddList(yytext); return IF;}
                    
"else"                { AddList(yytext); return ELSE;}

"for"                 { AddList(yytext); return FOR;}

"print"               { AddList(yytext); return PRINT;}

"println"             { AddList(yytext); return PRINTLN;}

"return"              { AddList(yytext); return RETURN;}

"to"                  { AddList(yytext); return TO;}

"var"                 { AddList(yytext); return VAR;}

"val"                 { AddList(yytext); return VAL;}

"while"               { AddList(yytext); return WHILE;}

"object"              { AddList(yytext); return OBJECT;}

"read"                { AddList(yytext); return READ;}


"boolean"             { AddList(yytext); yylval.valueType = new VALUETYPE(VALUETYPE::BOOLEAN); return VALUE_TYPE;}

"float"               { AddList(yytext); yylval.valueType = new VALUETYPE(VALUETYPE::FLOAT); return VALUE_TYPE;}

"int"                 { AddList(yytext); yylval.valueType = new VALUETYPE(VALUETYPE::INT); return VALUE_TYPE;}

"string"              { AddList(yytext); yylval.valueType = new VALUETYPE(VALUETYPE::STRING); return VALUE_TYPE;}

"char"                { AddList(yytext); yylval.valueType = new VALUETYPE(VALUETYPE::CHAR); return VALUE_TYPE;}


{integer}           {
                        AddList(yytext);
                        VALUE retValue = VALUE(stoi(string(yytext)));
                        yylval.value = new VALUE(retValue);

                        return VALUE_TOKEN;
                    }

true                {
                        AddList(yytext);
                        VALUE retValue = VALUE(true);
                        yylval.value = new VALUE(retValue);

                        return VALUE_TOKEN;
                    }
false               {
                        AddList(yytext);
                        VALUE retValue = VALUE(false);
                        yylval.value = new VALUE(retValue);

                        return VALUE_TOKEN;
                    }

{real}              {
                        AddList(yytext);
                        VALUE retValue = VALUE(true);
                        yylval.value = new VALUE(stof(string(yytext)));

                        return VALUE_TOKEN;
                    }

{identifier}        {
                        AddList(yytext);
                        yylval.idName = new string(yytext);

                        return ID_NAME;
                    }

{char}              {
                        AddList(yytext);
                        VALUE retValue = VALUE(true);
                        yylval.value = new VALUE(yytext[1]);

                        return VALUE_TOKEN;
                    }


[ \t\r]+            {AddList(yytext);}
\n                  {ListLine();}
.                   {yyerror("Unrecognized character detected!");}

%%

int yywrap(void){
    return 1;
}

