#include"project2.h"

// extern variables for lex
extern int yylineno;
extern char* yytext;

// extern variables for line
extern string lineBuffer;
extern int yylineno;  // defined and maintained in lex

// output the current line buffer
void AddList(char* token) {
    lineBuffer += string(token);
}

void ListLine() {
    // pretty print for the end of line
    DebugLog("Line " + to_string(yylineno) + " Finish Checking");
    DebugLog("========================\n");
    yylineno++;
    // pretty print for the starting of line
    DebugLog("========================");
    DebugLog("Line " + to_string(yylineno) + " Start Checking");

    // dont print anything from now
    // fprintf(yyout, "%d: %s\n", lineNumber, lineBuffer);
    // reset line buffer
    lineBuffer[0] = '\0';
}

// project2.h definition
ID::ID() {
    // set the id type
    idType = IDTYPE::INVALID;

    // id name
    IDName = "";
}

void ID::SetToFunction(string idName)
{
    this->IDName = idName;
    idType = IDTYPE::FUNCTION;
    retVal.valueType = VALUETYPE::UNSET;

    // successful message
    DebugLog("Function Declaration detected. Function name is " + this->IDName + "......OK");
}

void ID::SetToConstVar(string idName)
{
    this->IDName = idName;
    idType = IDTYPE::CONSTVAR;
    value.valueType = VALUETYPE::UNSET;

    // successful message
    DebugLog("Constant Variable Declaration detected. Constant var name is " + this->IDName + "......OK");
}

void ID::SetToVar(string idName)
{
    this->IDName = idName;
    idType = IDTYPE::VARIABLE;
    value.valueType = VALUETYPE::UNSET;

    // successful message
    DebugLog("Variable Declaration detected. Variable name is " + this->IDName + "......OK");
}

void ID::Dump()
{
    cout << "ID Dump Starts!\n";
    string idTypeString;
    if (this->idType == IDTYPE::INVALID) idTypeString = "invalid";
    if (this->idType == IDTYPE::CONSTVAR) idTypeString = "const var";
    if (this->idType == IDTYPE::FUNCTION) idTypeString = "function";
    if (this->idType == IDTYPE::VARIABLE) idTypeString = "variable";

    cout << "IDName -> " << this->IDName << ",\tIDType -> " << idTypeString;

    // function
    if (this->idType == IDTYPE::FUNCTION) {
        // print parameters
        cout << "\nParameters -> (";
        for (int i = 0; i < parameters.size(); i++) {
            parameters[i]->Dump();
            if (i != parameters.size() - 1)  cout << ", ";
            else cout << ")\t";
        }
        // print return value
        cout << "Return value -> ";
        retVal.Dump();
        cout << "\n";
    }
    // others idtype that shouldn't be invalid
    else if (this->idType != IDTYPE::INVALID) {
        // print value
        cout << "Value -> ";
        value.Dump();
        cout << "\n";
    }

    cout << "ID Dump Ends!\n";
}

// set value type for const and var
void ID::SetValueType(VALUETYPE valType)
{
    // id type checking
    // this function can only be used by const var and var
    if (idType == IDTYPE::CONSTVAR || idType == IDTYPE::VARIABLE) {
        // value type checking
        if (value.valueType == VALUETYPE::UNSET) {
            value.valueType = valType;

            // successful message
            DebugLog("Variable type declaration detected. Variable type is " + value.ValueTypeString() + "......OK");
        }
        // error handling as the value value type must be unset 
        else {
            throw (string("Value type has already setted to ") + 
                value.ValueTypeString() + string(". Value type can't be reset!")).c_str();
        }
    }
    else {
        throw (string("ID Type must be constant variable or variable to be setted its value type! Current ID Type is ") + 
            string(IdTypeToString(this->idType))).c_str();
    }
}

void ID::SetReturnType(VALUETYPE valType)
{
    // id type checking
    // this function can only be used by function type
    if (idType == IDTYPE::FUNCTION) {
        // value type checking
        if (retVal.valueType == VALUETYPE::UNSET) {
            retVal.valueType = valType;

            // successful message
            DebugLog("Function return declaration detected. Return Type is " + retVal.ValueTypeString() + "......OK");
        }
        // error handling as the value value type must be unset 
        else {
            throw (string("Function return type has already setted to ") +
                retVal.ValueTypeString() + string(". Function return value type can't be reset!"));
        }
    }
    else {
        throw (string("ID Type must be function to be setted its return value type! Current ID Type is ") +
            string(IdTypeToString(this->idType)));
    }
}

// push back parameter for the function
void ID::AddParameter(ID id)
{
    // check the function parameter for no duplicate names
    this->parameters.push_back(new ID(id));

    // print successful message
    DebugLog("Function argument declaration detected, argument name is " +
        id.IDName + ", Argument value type is " + id.value.ValueTypeString() + "......OK");
}

// init value could be used by var and const var
void ID::InitValue(VALUE value)
{
    if (idType == IDTYPE::CONSTVAR || idType == IDTYPE::VARIABLE) {
        if (this->value.valueType == value.valueType || this->value.valueType == VALUETYPE::UNSET) {
            this->value.valueType = value.valueType;
            this->value = value;
        }
        else throw string("Variable value type is " + this->value.ValueTypeString() + ", but the value type assigned is "
            + value.ValueTypeString());
    }
    else {
        throw string("Only ID type that is constant variable and variable can init its values");
    }
}

// set value can only used by var
void ID::SetValue(VALUE value)
{
    if (idType == IDTYPE::VARIABLE) {
        if (this->value.valueType == value.valueType) {
            this->value = value;
        }
        else throw string("Variable value type is " + this->value.ValueTypeString() + ", but the value type assigned is "
            + value.ValueTypeString());
    }
    else {
        throw string("Only ID type that is variable can change its values");
    }
}

VALUE::VALUE() {
    valueType = VALUETYPE::INVALID;

    ival = 0;
    fval = 0;
    sval = "";
    bval = false;
    cval = 0;
}

// constructor for different types (type could defined explicitly/implicitly)
// below constructor is non array values
VALUE::VALUE(int ival, VALUETYPE valueType) {
    // if user set the valuetype explicitly, check value type passed in
    if (valueType != VALUETYPE::INT) {
        throw (string("Provided value type is int, but the value type at declaration is ") + 
            valueTypeToString(valueType));
    }

    this->valueType = valueType;

    this->ival = ival;
    fval = 0;
    sval = "";
    bval = false;
    cval = 0;
}

VALUE::VALUE(float fval, VALUETYPE valueType) {
    // if user set the valuetype explicitly, check value type passed in
    if (valueType != VALUETYPE::FLOAT) {
        throw (string("Provided value type is float, but the value type at declaration is ") +
            valueTypeToString(valueType));
    }

    this->valueType = valueType;

    ival = 0;
    this->fval = fval;
    sval = "";
    bval = false;
    cval = 0;
}

VALUE::VALUE(string sval, VALUETYPE valueType) {
    // if user set the valuetype explicitly, check value type passed in
    if (valueType != VALUETYPE::STRING) {
        throw (string("Provided value type is string, but the value type at declaration is ") +
            valueTypeToString(valueType));
    }

    this->valueType = valueType;

    ival = 0;
    fval = 0;
    this->sval = sval;
    bval = false;
    cval = 0;
}

VALUE::VALUE(bool bval, VALUETYPE valueType) {
    // if user set the valuetype explicitly, check value type passed in
    if (valueType != VALUETYPE::BOOLEAN) {
        throw (string("Provided value type is bool, but the value type at declaration is ") +
            valueTypeToString(valueType));
    }

    this->valueType = valueType;

    ival = 0;
    fval = 0;
    sval = "";
    this->bval = bval;
    cval = 0;
}

VALUE::VALUE(char cval, VALUETYPE valueType) {
    // if user set the valuetype explicitly, check value type passed in
    if (valueType != VALUETYPE::CHAR) {
        throw (string("Provided value type is char, but the value type at declaration is ") +
            valueTypeToString(valueType));
    }

    this->valueType = valueType;

    ival = 0;
    fval = 0;
    sval = "";
    bval = false;
    this->cval = cval;
}

// constructor for array values
VALUE::VALUE(VALUETYPE valueType, int range) {
    this->valueType = valueType;

    ival = 0;
    fval = 0;
    sval = "";
    bval = false;
    cval = 0;

    // check the range value to be larger than zero
    if (range <= 0) {
        throw string("Array Range should be larger than zero!");
    }

    // set vector size
    // char vector
    if (valueType == VALUETYPE::ARRCHAR) {
        cvals.resize((size_t)range);
    }
    // boolean vector
    else if (valueType == VALUETYPE::ARRBOOLEAN) {
        bvals.resize((size_t)range);
    }
    // string vector
    else if (valueType == VALUETYPE::ARRSTRING) {
        svals.resize((size_t)range);
    }
    // int vector
    else if (valueType == VALUETYPE::ARRINT) {
        ivals.resize((size_t)range);
    }
    // float vector
    else if (valueType == VALUETYPE::ARRFLOAT) {
        fvals.resize((size_t)range);
    }
    // this shouldn't be called
    else {
        throw string("I dont know how possible do you reach here!\n" 
            "Bug Found at VALUE::VALUE(VALUETYPE valueType, int range)\n");
    }
}

// operator overloading
VALUE operator+(const VALUE& lhs, const VALUE& rhs) {
    // type should be same
    if (lhs.valueType != rhs.valueType) throw string("Different value type cant do the add operation");
    // type should be int or float
    if (lhs.valueType != VALUETYPE::INT && lhs.valueType != VALUETYPE::FLOAT) throw string("Only value type int and float do the add operation");
    
    // successful message
    VALUE answerValue;
    answerValue.valueType = lhs.valueType;
    if (lhs.valueType == VALUETYPE::INT) answerValue.ival = lhs.ival + rhs.ival;
    else if (lhs.valueType == VALUETYPE::FLOAT) answerValue.fval = lhs.fval + rhs.fval;

    DebugLog("<" + valueTypeToString(lhs.valueType) + "> + <" + valueTypeToString(rhs.valueType) + "> detected......OK");
    return answerValue;
}

VALUE operator-(const VALUE& lhs, const VALUE& rhs) {
    // type should be same
    if (lhs.valueType != rhs.valueType) throw string("Different value type cant do the minus operation");
    // type should be int or float
    if (lhs.valueType != VALUETYPE::INT && lhs.valueType != VALUETYPE::FLOAT) throw string("Only value type int and float do the minus operation");

    // successful message
    VALUE answerValue;
    answerValue.valueType = lhs.valueType;
    if (lhs.valueType == VALUETYPE::INT) answerValue.ival = lhs.ival - rhs.ival;
    else if (lhs.valueType == VALUETYPE::FLOAT) answerValue.fval = lhs.fval - rhs.fval;

    DebugLog("<" + valueTypeToString(lhs.valueType) + "> - <" + valueTypeToString(rhs.valueType) + "> detected......OK");
    return answerValue;
}

VALUE operator*(const VALUE& lhs, const VALUE& rhs) {
    // type should be same
    if (lhs.valueType != rhs.valueType) throw string("Different value type cant do the mutiple operation");
    // type should be int or float
    if (lhs.valueType != VALUETYPE::INT && lhs.valueType != VALUETYPE::FLOAT) throw string("Only value type int and float do the mutiple operation");

    // successful message
    VALUE answerValue;
    answerValue.valueType = lhs.valueType;
    if (lhs.valueType == VALUETYPE::INT) answerValue.ival = lhs.ival * rhs.ival;
    else if (lhs.valueType == VALUETYPE::FLOAT) answerValue.fval = lhs.fval * rhs.fval;

    DebugLog("<" + valueTypeToString(lhs.valueType) + "> * <" + valueTypeToString(rhs.valueType) + "> detected......OK");
    return answerValue;
}

VALUE operator/(const VALUE& lhs, const VALUE& rhs) {
    // type should be same
    if (lhs.valueType != rhs.valueType) throw string("Different value type cant do the mutiple operation");
    // type should be int or float
    if (lhs.valueType != VALUETYPE::INT && lhs.valueType != VALUETYPE::FLOAT) throw string("Only value type int and float do the mutiple operation");

    // successful message
    VALUE answerValue;
    answerValue.valueType = lhs.valueType;
    if (lhs.valueType == VALUETYPE::INT) answerValue.ival = lhs.ival / rhs.ival;
    else if (lhs.valueType == VALUETYPE::FLOAT) answerValue.fval = lhs.fval / rhs.fval;

    DebugLog("<" + valueTypeToString(lhs.valueType) + "> / <" + valueTypeToString(rhs.valueType) + "> detected......OK");
    return answerValue;
}

VALUE operator%(const VALUE& lhs, const VALUE& rhs) {
    throw string("The owner didn't implemented the remainder operation");
}

VALUE& VALUE::operator[](int idx) {
    // check provided idx is larger or equal than zero
    if (idx < 0) {
        throw string("The index used in [] operator must be larger or equal than zero!");
    }
    VALUE& answerValue = *this;

    // check whether is array or not
    // bool
    if (valueType == VALUETYPE::ARRBOOLEAN) {
        // check provided idx doesn't exceed the range
        if (bvals.size() <= idx) {
            throw string("The index used in [] operator exceed the size of boolean array!");
        }
        else {
            answerValue.valueType = VALUETYPE::BOOLEAN;
            answerValue.bval = bvals[idx];
        }
    }

    // char
    else if (valueType == VALUETYPE::ARRCHAR) {
        // check provided idx doesn't exceed the range
        if (cvals.size() <= idx) {
            throw string("The index used in [] operator exceed the size of char array!");
        }
        else {
            answerValue.valueType = VALUETYPE::CHAR;
            answerValue.cval = cvals[idx];
        }
    }

    // string
    else if (valueType == VALUETYPE::ARRSTRING) {
        // check provided idx doesn't exceed the range
        if (svals.size() <= idx) {
            throw string("The index used in [] operator exceed the size of string array!");
        }
        else {
            answerValue.valueType = VALUETYPE::STRING;
            answerValue.sval = svals[idx];
        }
    }

    // float
    else if (valueType == VALUETYPE::ARRFLOAT) {
        // check provided idx doesn't exceed the range
        if (fvals.size() <= idx) {
            throw string("The index used in [] operator exceed the size of float array!");
        }
        else {
            answerValue.valueType = VALUETYPE::FLOAT;
            answerValue.fval = fvals[idx];
        }
    }

    // int
    else if (valueType == VALUETYPE::ARRINT) {
        // check provided idx doesn't exceed the range
        if (ivals.size() <= idx) {
            throw string("The index used in [] operator exceed the size of int array!");
        }
        else {
            answerValue.valueType = VALUETYPE::INT;
            answerValue.ival = ivals[idx];
        }
    }
    
    // return successful message
    DebugLog("[] operator detected......OK");
    return answerValue;
}

// return value type string
string VALUE::ValueTypeString() {
    return valueTypeToString(valueType);
}

void VALUE::Dump()
{
    if (valueType == VALUETYPE::INVALID);
    else if (valueType == VALUETYPE::ARRBOOLEAN) {
        cout << "ValueType -> Arr Boolean";
        cout << " | ValueValue -> (";
        for (int i = 0; i < bvals.size(); i++) {
            cout << bvals[i];

            if (i != bvals.size() - 1)  cout << ", ";
            else cout << ")";
        }
    }
    else if (valueType == VALUETYPE::ARRCHAR) {
        cout << "ValueType -> Arr Char";
        cout << " | ValueValue -> (";
        for (int i = 0; i < cvals.size(); i++) {
            cout << cvals[i];

            if (i != cvals.size() - 1)  cout << ", ";
            else cout << ")";
        }
    }
    else if (valueType == VALUETYPE::ARRFLOAT) {
        cout << "ValueType -> Arr Double";
        cout << " | ValueValue -> (";
        for (int i = 0; i < fvals.size(); i++) {
            cout << fvals[i];

            if (i != fvals.size() - 1)  cout << ", ";
            else cout << ")";
        }
    }
    else if (valueType == VALUETYPE::ARRINT) {
        cout << "ValueType -> Arr Integer";
        cout << " | ValueValue -> (";
        for (int i = 0; i < ivals.size(); i++) {
            cout << ivals[i];

            if (i != ivals.size() - 1)  cout << ", ";
            else cout << ")";
        }
    }
    else if (valueType == VALUETYPE::ARRSTRING) {
        cout << "ValueType -> Arr String";
        cout << " | ValueValue -> (";
        for (int i = 0; i < svals.size(); i++) {
            cout << svals[i];

            if (i != svals.size() - 1)  cout << ", ";
            else cout << ")";
        }
    }
    else if (valueType == VALUETYPE::VOID) {
        cout << "ValueType -> Void";
    }
    else if (valueType == VALUETYPE::BOOLEAN) {
        cout << "ValueType -> Boolean";
        cout << " | ValueValue -> (" << bval << ")";
    }
    else if (valueType == VALUETYPE::CHAR) {
        cout << "ValueType -> Char";
        cout << " | ValueValue -> (" << cval << ")";
    }
    else if (valueType == VALUETYPE::FLOAT) {
        cout << "ValueType -> Double";
        cout << " | ValueValue -> (" << fval << ")";
    }
    else if (valueType == VALUETYPE::INT) {
        cout << "ValueType -> Integer";
        cout << " | ValueValue -> (" << ival << ")";
    }
    else if (valueType == VALUETYPE::STRING) {
        cout << "ValueType -> String";
        cout << " | ValueValue -> (" << sval << ")";
    }

}

void Symbol::Dump()
{
    for (int i = 0; i < ids.size(); i++) {
        cout << "\n";
        ids[i].Dump();
        cout << "\n";
    }
}

void SymbolTable::CreateSymbol()
{
    this->validSymbols.push_back(Symbol());
}

void SymbolTable::DropSymbol()
{
    Symbol symbol = this->validSymbols.back();
    this->validSymbols.pop_back();
    this->invalidSymbols.push_back(symbol);
}

ID& SymbolTable::LookUp(string IDName)
{
    // look up for the current scope first
    for (int i = validSymbols.size() - 1; i >= 0; i--) {
        for (int j = 0; j < validSymbols[i].ids.size(); j++) {
            // found same id with the name
            if (IDName == validSymbols[i].ids[j].IDName) {
                return validSymbols[i].ids[j];
            }
        }
    }

    // else look up not found
    throw string("Error found in function SymbolTable::LookUp(string IDName)\nIDName pass in didn't found in symbol table!\n");
}

ID& SymbolTable::Insert(ID id)
{
    // get the symbol from the current scope
    int i = validSymbols.size() - 1;
    // check whether has same id name inside the current scope
    for (int j = 0; j < validSymbols[i].ids.size(); j++) {
        // the id with same name already declare in this scope
        if (validSymbols[i].ids[j].IDName == id.IDName) {
            throw ("A same ID name " + validSymbols[i].ids[j].IDName + " found has already declared in this scope with id type "
                + IdTypeToString(validSymbols[i].ids[j].idType));
        }
    }

    validSymbols[i].ids.push_back(id);
    return validSymbols[i].ids[validSymbols[i].ids.size() - 1];
}

void SymbolTable::DumpValidSymbols()
{
    for (int i = 0; i < validSymbols.size(); i++) {
        cout << "\n";
        validSymbols[i].Dump();
        cout << "\n";
    }
}

void SymbolTable::DumpInvalidSymbols()
{
    for (int i = 0; i < invalidSymbols.size(); i++) {
        cout << "\n";
        invalidSymbols[i].Dump();
        cout << "\n";
    }
}

void DebugLog(string log, bool hasLine) {
    if (hasLine) cout << log << '\n';
    else cout << log;
}

string IdTypeToString(IDTYPE idtype) {
    switch (idtype)
    {
    case IDTYPE::INVALID:
        return "Invalid";
        break;
    case IDTYPE::CONSTVAR:
        return "Const Variable";
        break;
    case IDTYPE::VARIABLE:
        return "Variable";
        break;
    case IDTYPE::FUNCTION:
        return "Function";
        break;

    default:
        throw string("ID type provided doesn't found!");
        return "Invalid";
        break;
    }
}

string valueTypeToString(VALUETYPE valueType) {
    switch (valueType)
    {
    case VALUETYPE::INVALID:
        return "Invalid";
        break;
    case VALUETYPE::UNSET:
        return "Unset";
        break;
    case VALUETYPE::VOID:
        return "Void";
        break;
    case VALUETYPE::STRING:
        return "String";
        break;
    case VALUETYPE::CHAR:
        return "Char";
        break;
    case VALUETYPE::INT:
        return "Int";
        break;
    case VALUETYPE::FLOAT:
        return "Float";
        break;
    case VALUETYPE::BOOLEAN:
        return "Boolean";
        break;
    case VALUETYPE::ARRSTRING:
        return "ArrString";
        break;
    case VALUETYPE::ARRCHAR:
        return "ArrChar";
        break;
    case VALUETYPE::ARRINT:
        return "ArrInt";
        break;
    case VALUETYPE::ARRFLOAT:
        return "ArrFloat";
        break;
    case VALUETYPE::ARRBOOLEAN:
        return "ArrBoolean";
        break;

    default:
        throw string("Value Type provided not found!");
        return "Invalid";
        break;
    }
}
