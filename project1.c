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
}

void tokenOperator(char* type, char* token){
    fprintf(yyout, "<%s: \"%s\">\n", type, token);
}

void tokenKeyword(char* token) {
    fprintf(yyout, "<%s>\n", stringToUpper(token));
}

void tokenType(char* type, char* token) {
    fprintf(yyout, "<%s: %s>\n", type, token);
}

// output the current line buffer
void addList(char* token){
    strcat(lineBuffer, token);
}

void listLine(){
    lineNumber++;
    fprintf(yyout, "%d: %s\n", lineNumber, lineBuffer);
    // reset line buffer
    lineBuffer[0] = '\0';
}

// error handling
void handleError(char* expectedVal, char* errorString){
    fprintf(yyout, "Semantic error in line %d. Expected an %s but found %s\n", lineNumber+1, expectedVal, errorString);
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