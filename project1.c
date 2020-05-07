#include<stdio.h>
#include"project1.h"

extern int yylex();
extern int yylineno;
extern char* yytext;

int main(int argc, char* argv[]){
    yylex();
    return 0;
}