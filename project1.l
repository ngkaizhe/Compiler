%{
#include"stdio.h"
#define token(t) {printf("<%s>\n", t);}

// definitions
// tokens that will be recognized
// character set
// delimiters
// arithmetic, relational, and logical operators
// identifiers(a string of letters and digits beginning with a letter)
// integer constants
// boolean constants
// real constants
// string constants("aa""bb")

// tokens that will be discarded
// whitespace
// comments
%}

%%
.* token(yytext)
\n printf("newline found!\n");

%%

int yywrap(void){
    return 1;
}

int main(int argc, char* argv[]){
    yylex();
    return 0;
}