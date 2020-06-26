#ifndef PROJECT3_H
#define PROJECT3_H

#include <vector>
#include <string>
#include <iostream>
using namespace std;

// newline
// list out the current line to check
void AddList(char *token);
void ListLine();

// symbol table

enum class IDTYPE
{
    INVALID,

    FUNCTION,
    CONSTVAR,
    VARIABLE,
    GLOBALVAR,
    OBJECTID,
};

enum class VALUETYPE
{
    INVALID, // invalid is when idtype and id is setted, but they wont use the value(eg-> value type = double, then value type of ival should be invalid)
    UNSET,   // when idtype and id is setted, but they no yet set the value

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

class VALUE
{
public:
    VALUE();
    // constructor for different types (type could defined explicitly/implicitly)
    // below constructor is non array values
    VALUE(int ival, VALUETYPE valueType = VALUETYPE::INT);
    VALUE(float fval, VALUETYPE valueType = VALUETYPE::FLOAT);
    VALUE(string sval, VALUETYPE valueType = VALUETYPE::STRING);
    VALUE(bool bval, VALUETYPE valueType = VALUETYPE::BOOLEAN);
    VALUE(char cval, VALUETYPE valueType = VALUETYPE::CHAR);

    // constructor for array values
    VALUE(VALUETYPE valueType, int range);

    // operator overloading
    // mathematics
    friend VALUE operator+(const VALUE &lhs, const VALUE &rhs);
    friend VALUE operator-(const VALUE &lhs, const VALUE &rhs);
    friend VALUE operator*(const VALUE &lhs, const VALUE &rhs);
    friend VALUE operator/(const VALUE &lhs, const VALUE &rhs);
    friend VALUE operator%(const VALUE &lhs, const VALUE &rhs);
    VALUE &operator[](int idx);
    // logical operators
    friend VALUE operator||(const VALUE &lhs, const VALUE &rhs);
    friend VALUE operator&&(const VALUE &lhs, const VALUE &rhs);
    friend VALUE operator<(const VALUE &lhs, const VALUE &rhs);
    friend VALUE operator<=(const VALUE &lhs, const VALUE &rhs);
    friend VALUE operator>(const VALUE &lhs, const VALUE &rhs);
    friend VALUE operator>=(const VALUE &lhs, const VALUE &rhs);
    friend VALUE operator==(const VALUE &lhs, const VALUE &rhs);
    friend VALUE operator!=(const VALUE &lhs, const VALUE &rhs);
    // unary operators
    VALUE operator-();
    VALUE operator!();

    // return value type string
    string ValueTypeString();

    // list out all information of this value
    void Dump();

    // the value below should be setted as private
    // but since we can't determine the return type
    // so the only way to get the value should dynamic check
    // the value type
    // but since this is the syntax analyze we wont assign any value
    // inside yet
    // just only type checking

    // the value type
    VALUETYPE valueType;

    // only constant will used these
    // only one of the value below will be used
    // the value
    int ival;
    float fval;
    string sval;
    bool bval;
    char cval;
    vector<int> ivals;
    vector<float> fvals;
    vector<string> svals;
    vector<bool> bvals;
    vector<char> cvals;
};

class ID
{
public:
    ID();

    // set idtype here
    // set to function
    void SetToFunction(string idName);
    // set to const var
    void SetToConstVar(string idName);
    // set to var
    void SetToVar(string idName);

    // set value type here
    // var/const var
    // this is going to set the value type explicitly
    void SetValueType(VALUETYPE valType);
    // function
    void SetReturnType(VALUETYPE valType);
    void AddParameter(ID valType);

    // init value could be used by var and const var
    void InitValue(VALUE value);

    // set value can only used by var
    void SetValue(VALUE value);

    // dump out the id values
    void Dump();

    // variables
    // we dont set it to private as it will be very hard to maintain the codes

    // id type
    IDTYPE idType;
    // id name
    string IDName;

    // will only used by function
    vector<ID *> parameters;
    // return type for function
    VALUE retVal;

    // value type for var and constant var
    VALUE value;

    // only variable will used these
    int scopeIndex;
};

class Symbol
{
public:
    void Dump();

    vector<ID *> ids;

    // the id that owns this Symbol
    // only used by object scope and function scope
    ID *parentIDPtr;
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
    ID *LookUp(string IDName);

    // insert the ID into the current scope
    ID *Insert(ID *id);

    // check whether current scope is global scope
    bool isGlobalScope(string IDName);
    // same as the function above, but only used in initialized
    bool isGlobalScope();

    // print all value in the current symbol table
    void DumpValidSymbols();
    void DumpInvalidSymbols();
};

// helper debug function
void DebugLog(string log, bool hasLine = true);

// enum class to string
string IdTypeToString(IDTYPE idtype);

string valueTypeToString(VALUETYPE valueType);

#endif