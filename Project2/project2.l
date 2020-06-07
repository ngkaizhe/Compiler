%{
#include "project2.h"

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
squarebracket   [[\]]
bracket         [{}]
/*arithmetic, relational, and logical operators*/
arithmetic      [\+\-*\/]

relational      [<>](=)?|[=!]=
logical         (&&)|(\|\|)|(!)
assignment      [=]

/*identifiers*/
identifier      [a-zA-Z][A-za-z0-9]*
/*constants*/
integer         [0-9]+
real            [0-9]+"."[0-9]+([Ee][+-]?[0-9]+)?


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

    yylval.value = new VALUE(string(yytext));

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


{comma}             {AddList(yytext);}
{colon}             {AddList(yytext);}
{period}            {AddList(yytext);}
{semicolon}         {AddList(yytext);}
{parenthese}        {AddList(yytext);}
{squarebracket}     {AddList(yytext);}
{bracket}           {AddList(yytext);}

{arithmetic}        {AddList(yytext); return yytext[0];}

{relational}        {AddList(yytext);}
{logical}           {AddList(yytext);}
{assignment}        {AddList(yytext); return yytext[0];}

{keyword}           {AddList(yytext);}
{typekeyword}       {AddList(yytext);}

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

