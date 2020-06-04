#include"project2.h"

// extern variables for lex
extern int yylex();
extern int yylineno;
extern char* yytext;
extern FILE* yyin;
extern FILE* yyout;

// extern variables for line
extern char lineBuffer[];
extern int lineNumber;
extern struct SymbolTable* symbolTable;

int main(int argc, char* argv[]) {
    yyin = fopen(argv[1], "r");
    yyout = fopen(argv[2], "w");
    symbolTable = (struct SymbolTable*) malloc(sizeof(struct SymbolTable*) * 1);
    Create(symbolTable);
    if(yyin != NULL){
        yylex();
        Dump(symbolTable);
        fclose(yyin);
        fclose(yyout);
    }
    else if(yyin == NULL){
        printf("Input file not found!\n");
    }
    return 0;
}

// output token value with specific format
void TokenNonType(char* token){
    fprintf(yyout, "<'%s'>\n", token);
}

void TokenOperator(char* type, char* token){
    fprintf(yyout, "<%s: %s>\n", type, token);
}

void TokenKeyword(char* token) {
    fprintf(yyout, "<%s>\n", StringToUpper(token));
}

void TokenType(char* type, char* token) {
    fprintf(yyout, "<%s: %s>\n", type, token);
}

// output the current line buffer
void AddList(char* token){
    strcat(lineBuffer, token);
}

void ListLine(){
    lineNumber++;
    fprintf(yyout, "%d: %s\n", lineNumber, lineBuffer);
    // reset line buffer
    lineBuffer[0] = '\0';
}

// error handling
void HandleError(char* expectedVal, char* errorString){
    fprintf(yyout, "Semantic error in line %d. Expected an %s but found %s\n", lineNumber+1, expectedVal, errorString);
    AddList(errorString);
}

// output the upper format of the input string
char* StringToUpper(char* s){
    char* ret = malloc (sizeof (char) * MAX);

    for(int i=0; s[i] != '\0'; i++){
        ret[i] = toupper(s[i]);
    }

    return ret;
}

// create
void Create(struct SymbolTable* symbolTable) {
    symbolTable->size = SYMBOLTABLESIZE;
    for (int i = 0; i < symbolTable->size; i++) {
        symbolTable->symbolArrays = (struct SymbolArray*) malloc(sizeof(struct SymbolArray) * symbolTable->size);
        // init
        symbolTable->symbolArrays[i].size = 0;
        symbolTable->symbolArrays[i].maxSize = SYMBOLARRAYSIZE;
        symbolTable->symbolArrays[i].values = (char**) malloc(sizeof(char*) * symbolTable->symbolArrays[i].maxSize);
    }
}

// lookup
int Lookup(struct SymbolTable* symbolTable, char* s) {
    for (int i = 0; i < symbolTable->size; i++) {
        struct SymbolArray* temp = &symbolTable->symbolArrays[i];
        for (int j = 0; j < temp->size; j++) {
            if (strcmp(temp->values[j], s) == 0) return i;
        }
    }
    // return hash(symbolTable, s);
    return -1;
}

// insert
int Insert(struct SymbolTable* symbolTable, char* s) {
    // get hash index
    int index = Hash(symbolTable, s);
    struct SymbolArray* temp = &symbolTable->symbolArrays[index];

    // check whether there is a duplicate string in our values
    // if have, then discard
    for(int i=0;i < temp->size; i++){
        // discard
        if(strcmp(temp->values[i], s) == 0) return index;
    }

    // check last index
    temp->values[temp->size] = (char*) malloc(sizeof(char) * (strlen(s) + 1));
    // strcpy_s(temp->values[temp->size], (strlen(s) + 1), s);
    memcpy(temp->values[temp->size], s, strlen(s) + 1);
    temp->size++;

    // too much value, exhausted so we reextended
    if (temp->size >= temp->maxSize) {
        char** tempVal = (char**) malloc(sizeof(char*) * temp->maxSize);
        memcpy(tempVal, temp->values, sizeof(char*) * temp->maxSize);

        temp->values = (char**) malloc(sizeof(char*) * temp->maxSize * 2);
        memcpy(temp->values, tempVal, sizeof(char*) * temp->maxSize);
        temp->maxSize *= 2;
    }

    return index;
}

// dump
void Dump(struct SymbolTable* symbolTable) {
    fprintf(yyout, "\nSymbol Table:\n");
    for (int i = 0; i < symbolTable->size; i++) {
        struct SymbolArray* temp = &symbolTable->symbolArrays[i];
        for (int j = 0; j < temp->size; j++) {
            fprintf(yyout, "%s\n", temp->values[j]);
        }
    }
}

// hash
int Hash(struct SymbolTable* symbolTable, char* s){
    int size = symbolTable->size;
    unsigned int hash = 0;
	int c;

	while (c = *s++)
	    hash += c;

	return hash % size;
}