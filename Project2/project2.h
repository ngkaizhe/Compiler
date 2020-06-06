#ifndef PROJECT2_H
#define PROJECT2_H 

#include<vector>
#include<string>
#include<iostream>
using namespace std;

// newline
// list out the current line to check
void AddList(char* token);
void ListLine();

// symbol table

enum class IDTYPE {
    INVALID,

    FUNCTION,
    CONSTVAR,
    VARIABLE,
};

enum class VALUETYPE {
    INVALID, // invalid is when idtype and id is setted, but they wont use the value(eg-> value type = double, then value type of ival should be invalid)
    UNSET, // when idtype and id is setted, but they no yet set the value

    VOID,
    STRING,
    CHAR,
    INT,
    FLOAT,
    BOOLEAN,

    ARRSTRING,
    ARRCHAR,
    ARRINT,
    ARRFLOAT,
    ARRBOOLEAN,
};

class VALUE {
public:
    VALUE();

    void Dump();

    VALUETYPE valueType;

    // only one of the value below will be used
    // the value
    int ival;
    double fval;
    string sval;
    bool bval;
    char cval;

    // if the value is array type
    vector<int> ivals;
    vector<double> dvals;
    vector<string> svals;
    vector<bool> bvals;
    vector<char> cvals;
};

class ID {
public:
    ID();

    // set idname
    ID(string idName);

    // set idtype here
    // set to function
    void SetToFunction();
    // set to const var
    void SetToConstVar();
    // set to var
    void SetToVar();

    // set value type here
    // var/const var
    // this is going to set the value type explicitly
    void SetValueType(VALUETYPE valType);
    // function
    void SetReturnType(VALUETYPE valType);
    void AddParameter(ID valType);

    // set value for const at declaration
    // will set the type implicitly if the type wasn't set
    void SetConstValue(char cval);
    void SetConstValue(double fval);
    void SetConstValue(string sval);
    void SetConstValue(int ival);
    void SetConstValue(vector<char> cvals);
    void SetConstValue(vector<double> dvals);
    void SetConstValue(vector<string> svals);
    void SetConstValue(vector<int> ivals);

    // set value for var only
    // will set the type implicitly if the type wasn't set
    void SetValue(char cval);
    void SetValue(double fval);
    void SetValue(string sval);
    void SetValue(int ival);
    void SetValue(vector<char> cvals);
    void SetValue(vector<double> dvals);
    void SetValue(vector<string> svals);
    void SetValue(vector<int> ivals);

    // dump out the id values
    void Dump();

// variables
// we dont set it to private as it will be very hard to maintain the codes

    // id type
    IDTYPE idType;
    // id name
    string IDName;

    // will only used by function
    vector<ID*> parameters;
    // return type for function
    VALUE retVal;

    // value type
    VALUE value;
};

class Symbol
{
public:
    void Dump();

    vector<ID> ids;
};

class SymbolTable
{
private:
    // the valid symbols that we are using
    vector<Symbol> validSymbols;
    // symbols that are already out of scope
    vector<Symbol> invalidSymbols;

public:
    SymbolTable(){};

    // create symbol if we reached a new scope
    void CreateSymbol();

    // drop symbol for different scope
    void DropSymbol();

    // look up the id name in the current scope or the larger scope
    ID LookUp(string IDName);
    
    // insert the ID into the current scope
    void Insert(ID id);

    // print all value in the current symbol table
    void DumpValidSymbols();
    void DumpInvalidSymbols();
};

// helper debug function
void DebugLog(string log);

#endif