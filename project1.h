#ifndef PROJECT1_H
#define PROJECT1_H 

#include <ctype.h>
#include <stdlib.h>
#include<stdio.h>
#include<string.h>
#define MAX 256

// default print out token
void tokenNonType(char* token);
// definitions
// tokens that will be recognized
// arithmetic, relational, and logical operators
void tokenOperator(char* type, char* token);

// keyword
void tokenKeyword(char* token);

// identifiers(a string of letters and digits beginning with a letter)
// integer constants
// boolean constants
// real constants
// string constants("aa""bb")
void tokenType(char* type, char* token);
// tokens that will be discarded
// whitespace
// comments

// newline
// list out the current line to check
void addList(char* token);
void listLine();

void handleError(char* errorString);

/*help function*/
char* stringToUpper(char* s);
#endif