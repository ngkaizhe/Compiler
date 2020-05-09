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
extern struct SymbolTable symbolTable;

int main(int argc, char* argv[]){
    // yyin = fopen(argv[1], "r");
    // yyout = fopen(argv[2], "w");
    // if(yyin != NULL){
    //     yylex();
    //     fclose(yyin);
    //     fclose(yyout);
    // }
    // else if(yyin == NULL){
    //     printf("Input file not found!\n");
    // }

    
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

// create
void create(struct SymbolTable symbolTable){
    symbolTable.size = SYMBOLTABLESIZE;
    for(int i=0; i<symbolTable.size; i++){
        symbolTable.symbolArrays = malloc(sizeof(struct SymbolArray) * symbolTable.size);
        // init
        symbolTable.symbolArrays[i].size = 0;
        symbolTable.symbolArrays[i].maxSize = 256;
        symbolTable.symbolArrays[i].values = malloc(sizeof(char*) * symbolTable.symbolArrays[i].maxSize);
    }
}

// lookup
int lookup(struct SymbolTable symbolTable, char* s){
    for(int i=0; i<symbolTable.size; i++){
        struct SymbolArray* temp = &symbolTable.symbolArrays[i]; 
        for(int j=0; j<temp->size; j++){
            fprintf(yyout, "%s\n", temp->values[j]);
        }
    }
}

// insert
int insert(struct SymbolTable symbolTable, char* s){
    // get hash index
    int index = 0;
    struct SymbolArray* temp = &symbolTable.symbolArrays[index];

    // check last index
    temp->values[temp->size] = malloc(sizeof(char) * strlen(s));
    memcpy(temp->values[temp->size], s, strlen(s));
    temp->size++;

    // too much value, exhausted
    if(temp->size > temp->maxSize){
        char** tempVal = malloc(sizeof(char*) * temp->maxSize);
        memcpy(tempVal, temp->values, sizeof(char*) * temp->maxSize);

        temp->values = malloc(sizeof(char*) * temp->maxSize * 2);
        memcpy(temp->values, tempVal, sizeof(char*) * temp->maxSize);
        temp->maxSize *= 2;
    }
}

// dump
void dump(struct SymbolTable symbolTable){
    fprintf(yyout, "\nSymbol Table:\n");
    for(int i=0; i<symbolTable.size; i++){
        struct SymbolArray* temp = &symbolTable.symbolArrays[i]; 
        for(int j=0; j<temp->size; j++){
            fprintf(yyout, "%s\n", temp->values[j]);
        }
    }
}