#ifndef PROJECT2_H
#define PROJECT2_H 

#include <ctype.h>
#include <stdlib.h>
#include<stdio.h>
#include<string.h>

#define MAX 1024

// default print out token
void TokenNonType(char* token);
// definitions
// tokens that will be recognized
// arithmetic, relational, and logical operators
void TokenOperator(char* type, char* token);

// keyword
void TokenKeyword(char* token);

// identifiers(a string of letters and digits beginning with a letter)
// integer constants
// boolean constants
// real constants
// string constants("aa""bb")
void TokenType(char* type, char* token);
// tokens that will be discarded
// whitespace
// comments

// newline
// list out the current line to check
void AddList(char* token);
void ListLine();

void HandleError(char* expectedVal, char* errorString);

/*help function*/
char* StringToUpper(char* s);

// symbol table
#define SYMBOLTABLESIZE 1
#define SYMBOLARRAYSIZE 1

struct SymbolArray
{
    char** values;
    int size;
    int maxSize;
};

struct SymbolTable
{
    struct SymbolArray* symbolArrays;
    int size;
};

// create
void Create(struct SymbolTable* symbolTable);

// lookup
int Lookup(struct SymbolTable* symbolTable, char* s);

// insert
int Insert(struct SymbolTable* symbolTable, char* s);

// dump
void Dump(struct SymbolTable* symbolTable);

// hash
int Hash(struct SymbolTable* symbolTable, char* s);

#endif