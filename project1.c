#include"project1.h"

// extern variables for lex
extern int yylex();
extern int yylineno;
extern char* yytext;
extern FILE* yyin;
extern FILE* yyout;

// extern variables for line
extern char lineBuffer[];
extern int lineNumber;

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

// output token value with specific format
void tokenNonType(char* token){
    fprintf(yyout, "<'%s'>\n", token);
    addList(token);
}

void tokenOperator(char* type, char* token){
    fprintf(yyout, "<%s: '%s'>\n", type, token);
    addList(token);
}

void tokenKeyword(char* token) {
    fprintf(yyout, "<%s>\n", stringToUpper(token));
    addList(token);
}

void tokenType(char* type, char* token) {
    fprintf(yyout, "<%s: %s>\n", type, token);
    addList(token);
}

// output the current line buffer
void addList(char* token){
    strcat(lineBuffer, token);
}

void listLine(){
    lineNumber++;
    fprintf(yyout, "Line %d: %s\n\n", lineNumber, lineBuffer);
    // reset line buffer
    lineBuffer[0] = '\0';
}

// error handling
void handleError(char* errorString){
    fprintf(yyout, "Bad Character detected (%s) at Line %d\n", errorString, lineNumber+1);
    addList(errorString);
}

// output the upper format of the input string
char* stringToUpper(char* s){
    char* ret = malloc (sizeof (char) * MAX);

    for(int i=0; s[i] != '\0'; i++){
        ret[i] = toupper(s[i]);
    }

    return ret;
}