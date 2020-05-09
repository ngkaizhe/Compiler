#include"project1.h"

extern int yylex();
extern int yylineno;
extern char* yytext;
extern FILE* yyin;
extern FILE* yyout;

int main(int argc, char* argv[]){
    yyin = fopen(argv[1], "r");
    yyout = fopen(argv[2], "w");
    if(yyin != NULL){
        yylex();
        fclose(yyin);
        fclose(yyout);
    }
    else if(yyin == NULL){
        printf("Input file not found!\n");
    }
    return 0;
}

// helper function 
// default print out token
void tokenNonType(char* token){
    fprintf(yyout, "<'%s'>\n", token);
}
// definitions
// tokens that will be recognized
// arithmetic, relational, and logical operators

// keyword
void tokenKeyword(char* token) {
    fprintf(yyout, "<%s>\n", stringToUpper(token));
}

// identifiers(a string of letters and digits beginning with a letter)
// integer constants
// boolean constants
// real constants
// string constants("aa""bb")
void tokenType(char* type, char* token) {
    fprintf(yyout, "<%s : %s>\n", type, token);
}
// tokens that will be discarded
// whitespace
// comments

char* stringToUpper(char* s){
    char* ret = malloc (sizeof (char) * MAX);

    for(int i=0; s[i] != '\0'; i++){
        ret[i] = toupper(s[i]);
    }

    return ret;
}