#include "project3.h"

// extern variables for lex
extern int yylineno;
extern char *yytext;

// extern variables for line
extern string lineBuffer;

// extern variables for symbol table
extern SymbolTable symbolTable;

// output the debug message or not
bool isProject2 = true;

// output the current line buffer
void AddList(char *token)
{
    lineBuffer += string(token);
}

void ListLine()
{
    // dont print anything from now
    // fprintf(yyout, "%d: %s\n", lineNumber, lineBuffer);
    // reset line buffer
    lineBuffer[0] = '\0';
}

// project2.h definition
ID::ID()
{
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

    // we must check whether the idName is global variable or local variable
    if (symbolTable.isGlobalScope())
    {
        idType = IDTYPE::GLOBALVAR;
    }
    else
    {
        idType = IDTYPE::VARIABLE;
    }

    value.valueType = VALUETYPE::UNSET;

    // successful message
    DebugLog("Variable Declaration detected. Variable name is " + this->IDName + "......OK");
}

void ID::Dump()
{
    cout << "ID Dump Starts!\n";

    cout << "IDName -> " << this->IDName << ",\tIDType -> " << IdTypeToString(this->idType) << "|";

    // function
    if (this->idType == IDTYPE::FUNCTION)
    {
        // print parameters
        cout << "\nParameters -> (";
        for (int i = 0; i < parameters.size(); i++)
        {
            parameters[i]->Dump();
            if (i != parameters.size() - 1)
                cout << ", ";
            else
                cout << ")\t";
        }
        // print return value
        cout << "Return value -> ";
        retVal.Dump();
        cout << "\n";
    }
    // others idtype that shouldn't be invalid
    else if (this->idType != IDTYPE::INVALID)
    {
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
    if (idType == IDTYPE::CONSTVAR || idType == IDTYPE::VARIABLE || idType == IDTYPE::GLOBALVAR)
    {
        // value type checking
        if (value.valueType == VALUETYPE::UNSET)
        {
            value.valueType = valType;

            // successful message
            DebugLog("Variable type declaration detected. Variable type is " + value.ValueTypeString() + "......OK");
        }
        // error handling as the value value type must be unset
        else
        {
            throw(string("Value type has already setted to ") +
                  value.ValueTypeString() + string(". Value type can't be reset!"))
                .c_str();
        }
    }
    else
    {
        throw(string("ID Type must be constant variable or variable to be setted its value type! Current ID Type is ") +
              string(IdTypeToString(this->idType)))
            .c_str();
    }
}

void ID::SetReturnType(VALUETYPE valType)
{
    // id type checking
    // this function can only be used by function type
    if (idType == IDTYPE::FUNCTION)
    {
        // value type checking
        if (retVal.valueType == VALUETYPE::UNSET)
        {
            retVal.valueType = valType;

            // successful message
            DebugLog("Function return declaration detected. Return Type is " + retVal.ValueTypeString() + "......OK");
        }
        // error handling as the value value type must be unset
        else
        {
            throw(string("Function return type has already setted to ") +
                  retVal.ValueTypeString() + string(". Function return value type can't be reset!"));
        }
    }
    else
    {
        throw(string("ID Type must be function to be setted its return value type! Current ID Type is ") +
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
    if (idType == IDTYPE::CONSTVAR || idType == IDTYPE::VARIABLE || idType == IDTYPE::GLOBALVAR)
    {
        if (this->value.valueType == value.valueType || this->value.valueType == VALUETYPE::UNSET)
        {
            this->value.valueType = value.valueType;
            this->value = value;
        }
        else
            throw string("Variable value type is " + this->value.ValueTypeString() + ", but the value type assigned is " + value.ValueTypeString());
    }
    else
    {
        throw string("Only ID type that is constant variable and variable can init its values");
    }
}

// set value can only used by var
void ID::SetValue(VALUE value)
{
    if (idType == IDTYPE::VARIABLE || idType == IDTYPE::GLOBALVAR)
    {
        if (this->value.valueType == value.valueType)
        {
            this->value = value;
        }
        else
            throw string("Variable value type is " + this->value.ValueTypeString() + ", but the value type assigned is " + value.ValueTypeString());
    }
    else
    {
        throw string("Only ID type that is variable can change its values");
    }
}

VALUE::VALUE()
{
    valueType = VALUETYPE::INVALID;

    ival = 0;
    fval = 0;
    sval = "";
    bval = false;
    cval = 0;
}

// constructor for different types (type could defined explicitly/implicitly)
// below constructor is non array values
VALUE::VALUE(int ival, VALUETYPE valueType)
{
    // if user set the valuetype explicitly, check value type passed in
    if (valueType != VALUETYPE::INT)
    {
        throw(string("Provided value type is int, but the value type at declaration is ") +
              valueTypeToString(valueType));
    }

    this->valueType = valueType;

    this->ival = ival;
    fval = 0;
    sval = "";
    bval = false;
    cval = 0;
}

VALUE::VALUE(float fval, VALUETYPE valueType)
{
    // if user set the valuetype explicitly, check value type passed in
    if (valueType != VALUETYPE::FLOAT)
    {
        throw(string("Provided value type is float, but the value type at declaration is ") +
              valueTypeToString(valueType));
    }

    this->valueType = valueType;

    ival = 0;
    this->fval = fval;
    sval = "";
    bval = false;
    cval = 0;
}

VALUE::VALUE(string sval, VALUETYPE valueType)
{
    // if user set the valuetype explicitly, check value type passed in
    if (valueType != VALUETYPE::STRING)
    {
        throw(string("Provided value type is string, but the value type at declaration is ") +
              valueTypeToString(valueType));
    }

    this->valueType = valueType;

    ival = 0;
    fval = 0;
    this->sval = sval;
    bval = false;
    cval = 0;
}

VALUE::VALUE(bool bval, VALUETYPE valueType)
{
    // if user set the valuetype explicitly, check value type passed in
    if (valueType != VALUETYPE::BOOLEAN)
    {
        throw(string("Provided value type is bool, but the value type at declaration is ") +
              valueTypeToString(valueType));
    }

    this->valueType = valueType;

    ival = 0;
    fval = 0;
    sval = "";
    this->bval = bval;
    cval = 0;
}

VALUE::VALUE(char cval, VALUETYPE valueType)
{
    // if user set the valuetype explicitly, check value type passed in
    if (valueType != VALUETYPE::CHAR)
    {
        throw(string("Provided value type is char, but the value type at declaration is ") +
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
VALUE::VALUE(VALUETYPE valueType, int range)
{
    this->valueType = valueType;

    ival = 0;
    fval = 0;
    sval = "";
    bval = false;
    cval = 0;

    // check the range value to be larger than zero
    if (range <= 0)
    {
        throw string("Array Range should be larger than zero!");
    }

    // set vector size
    // char vector
    if (this->valueType == VALUETYPE::CHAR)
    {
        this->valueType = VALUETYPE::ARRCHAR;
        cvals.resize((size_t)range);
    }
    // boolean vector
    else if (this->valueType == VALUETYPE::BOOLEAN)
    {
        this->valueType = VALUETYPE::ARRBOOLEAN;
        bvals.resize((size_t)range);
    }
    // string vector
    else if (this->valueType == VALUETYPE::STRING)
    {
        this->valueType = VALUETYPE::ARRSTRING;
        svals.resize((size_t)range);
    }
    // int vector
    else if (this->valueType == VALUETYPE::INT)
    {
        this->valueType = VALUETYPE::ARRINT;
        ivals.resize((size_t)range);
    }
    // float vector
    else if (this->valueType == VALUETYPE::FLOAT)
    {
        this->valueType = VALUETYPE::ARRFLOAT;
        fvals.resize((size_t)range);
    }
    // this shouldn't be called
    else
    {
        throw string("I dont know how possible do you reach here!\n"
                     "Bug Found at VALUE::VALUE(VALUETYPE valueType, int range)\n");
    }
    DebugLog("Array declaration detected! Array value setted......OK");
}

// operator overloading
VALUE operator+(const VALUE &lhs, const VALUE &rhs)
{
    // type should be same
    if (lhs.valueType != rhs.valueType)
        throw string("Different value type cant do the add operation");
    // type should be int or float
    if (lhs.valueType != VALUETYPE::INT && lhs.valueType != VALUETYPE::FLOAT)
        throw string("Only value type int and float do the add operation");

    // successful message
    VALUE answerValue;
    answerValue.valueType = lhs.valueType;
    if (lhs.valueType == VALUETYPE::INT)
        answerValue.ival = lhs.ival + rhs.ival;
    else if (lhs.valueType == VALUETYPE::FLOAT)
        answerValue.fval = lhs.fval + rhs.fval;

    DebugLog("<" + valueTypeToString(lhs.valueType) + "> + <" + valueTypeToString(rhs.valueType) + "> detected......OK");
    return answerValue;
}

VALUE operator-(const VALUE &lhs, const VALUE &rhs)
{
    // type should be same
    if (lhs.valueType != rhs.valueType)
        throw string("Different value type cant do the minus operation");
    // type should be int or float
    if (lhs.valueType != VALUETYPE::INT && lhs.valueType != VALUETYPE::FLOAT)
        throw string("Only value type int and float do the minus operation");

    // successful message
    VALUE answerValue;
    answerValue.valueType = lhs.valueType;
    if (lhs.valueType == VALUETYPE::INT)
        answerValue.ival = lhs.ival - rhs.ival;
    else if (lhs.valueType == VALUETYPE::FLOAT)
        answerValue.fval = lhs.fval - rhs.fval;

    DebugLog("<" + valueTypeToString(lhs.valueType) + "> - <" + valueTypeToString(rhs.valueType) + "> detected......OK");
    return answerValue;
}

VALUE operator*(const VALUE &lhs, const VALUE &rhs)
{
    // type should be same
    if (lhs.valueType != rhs.valueType)
        throw string("Different value type cant do the mutiple operation");
    // type should be int or float
    if (lhs.valueType != VALUETYPE::INT && lhs.valueType != VALUETYPE::FLOAT)
        throw string("Only value type int and float do the mutiple operation");

    // successful message
    VALUE answerValue;
    answerValue.valueType = lhs.valueType;
    if (lhs.valueType == VALUETYPE::INT)
        answerValue.ival = lhs.ival * rhs.ival;
    else if (lhs.valueType == VALUETYPE::FLOAT)
        answerValue.fval = lhs.fval * rhs.fval;

    DebugLog("<" + valueTypeToString(lhs.valueType) + "> * <" + valueTypeToString(rhs.valueType) + "> detected......OK");
    return answerValue;
}

VALUE operator/(const VALUE &lhs, const VALUE &rhs)
{
    // type should be same
    if (lhs.valueType != rhs.valueType)
        throw string("Different value type cant do the divide operation");
    // type should be int or float
    if (lhs.valueType != VALUETYPE::INT && lhs.valueType != VALUETYPE::FLOAT)
        throw string("Only value type int and float do the divide operation");

    // successful message
    VALUE answerValue;
    answerValue.valueType = lhs.valueType;
    if (lhs.valueType == VALUETYPE::INT)
        answerValue.ival = lhs.ival / rhs.ival;
    else if (lhs.valueType == VALUETYPE::FLOAT)
        answerValue.fval = lhs.fval / rhs.fval;

    DebugLog("<" + valueTypeToString(lhs.valueType) + "> / <" + valueTypeToString(rhs.valueType) + "> detected......OK");
    return answerValue;
}

VALUE operator%(const VALUE &lhs, const VALUE &rhs)
{
    // type should be same
    if (lhs.valueType != rhs.valueType)
        throw string("Different value type cant do the remainder operation");
    // type should be int or float
    if (lhs.valueType != VALUETYPE::INT)
        throw string("Only value type int can do the remainder operation");

    // successful message
    VALUE answerValue;
    answerValue.valueType = lhs.valueType;
    if (lhs.valueType == VALUETYPE::INT)
        answerValue.ival = lhs.ival % rhs.ival;

    DebugLog("<" + valueTypeToString(lhs.valueType) + "> % <" + valueTypeToString(rhs.valueType) + "> detected......OK");
    return answerValue;
}

VALUE &VALUE::operator[](int idx)
{
    // check provided idx is larger or equal than zero
    if (idx < 0)
    {
        throw string("The index used in [] operator must be larger or equal than zero!");
    }
    VALUE &answerValue = *this;

    // check whether is array or not
    // bool
    if (valueType == VALUETYPE::ARRBOOLEAN)
    {
        // check provided idx doesn't exceed the range
        if (bvals.size() <= idx)
        {
            throw string("The index used in [] operator exceed the size of boolean array!");
        }
        else
        {
            answerValue.valueType = VALUETYPE::BOOLEAN;
            answerValue.bval = bvals[idx];
        }
    }

    // char
    else if (valueType == VALUETYPE::ARRCHAR)
    {
        // check provided idx doesn't exceed the range
        if (cvals.size() <= idx)
        {
            throw string("The index used in [] operator exceed the size of char array!");
        }
        else
        {
            answerValue.valueType = VALUETYPE::CHAR;
            answerValue.cval = cvals[idx];
        }
    }

    // string
    else if (valueType == VALUETYPE::ARRSTRING)
    {
        // check provided idx doesn't exceed the range
        if (svals.size() <= idx)
        {
            throw string("The index used in [] operator exceed the size of string array!");
        }
        else
        {
            answerValue.valueType = VALUETYPE::STRING;
            answerValue.sval = svals[idx];
        }
    }

    // float
    else if (valueType == VALUETYPE::ARRFLOAT)
    {
        // check provided idx doesn't exceed the range
        if (fvals.size() <= idx)
        {
            throw string("The index used in [] operator exceed the size of float array!");
        }
        else
        {
            answerValue.valueType = VALUETYPE::FLOAT;
            answerValue.fval = fvals[idx];
        }
    }

    // int
    else if (valueType == VALUETYPE::ARRINT)
    {
        // check provided idx doesn't exceed the range
        if (ivals.size() <= idx)
        {
            throw string("The index used in [] operator exceed the size of int array!");
        }
        else
        {
            answerValue.valueType = VALUETYPE::INT;
            answerValue.ival = ivals[idx];
        }
    }
    else
    {
        // error detected
        throw string("[] operator can only used on array value type!");
    }

    // return successful message
    DebugLog("[] operator detected......OK");
    return answerValue;
}

VALUE operator||(const VALUE &lhs, const VALUE &rhs)
{
    // only boolean value can do or operation
    if (lhs.valueType == VALUETYPE::BOOLEAN && rhs.valueType == VALUETYPE::BOOLEAN)
    {
        DebugLog("<BOOLEAN> || <BOOLEAN> detected!......OK");
        VALUE answer;
        answer.valueType = VALUETYPE::BOOLEAN;
        answer.bval = (lhs.bval || rhs.bval);
        return answer;
    }
    else
    {
        throw string("Only boolean value type can do OR operation!");
    }
}

VALUE operator&&(const VALUE &lhs, const VALUE &rhs)
{
    // only boolean value can do and operation
    if (lhs.valueType == VALUETYPE::BOOLEAN && rhs.valueType == VALUETYPE::BOOLEAN)
    {
        DebugLog("<BOOLEAN> && <BOOLEAN> detected!......OK");
        VALUE answer;
        answer.valueType = VALUETYPE::BOOLEAN;
        answer.bval = (lhs.bval && rhs.bval);
        return answer;
    }
    else
    {
        throw string("Only boolean value type can do AND operation!");
    }
}

VALUE operator<(const VALUE &lhs, const VALUE &rhs)
{
    // comparation operator must be same value type
    if (lhs.valueType != rhs.valueType)
        throw string("Less than operation can only work on same value type");

    if (lhs.valueType == VALUETYPE::FLOAT)
    {
        DebugLog("<FLAOT> < <FLOAT> detected!......OK");
        return VALUE(lhs.fval < rhs.fval);
    }

    else if (lhs.valueType == VALUETYPE::INT)
    {
        DebugLog("<INT> < <INT> detected!......OK");
        return VALUE(lhs.ival < rhs.ival);
    }

    else
    {
        throw string("Only int and float can do LESS THAN operation!");
    }
}

VALUE operator<=(const VALUE &lhs, const VALUE &rhs)
{
    // comparation operator must be same value type
    if (lhs.valueType != rhs.valueType)
        throw string("Less or equal than operation can only work on same value type");

    if (lhs.valueType == VALUETYPE::FLOAT)
    {
        DebugLog("<FLAOT> <= <FLOAT> detected!......OK");
        return VALUE(lhs.fval <= rhs.fval);
    }

    else if (lhs.valueType == VALUETYPE::INT)
    {
        DebugLog("<INT> <= <INT> detected!......OK");
        return VALUE(lhs.ival <= rhs.ival);
    }

    else
    {
        throw string("Only int and float can do Less or equal than operation!");
    }
}

VALUE operator>(const VALUE &lhs, const VALUE &rhs)
{
    // comparation operator must be same value type
    if (lhs.valueType != rhs.valueType)
        throw string("Greater than operation can only work on same value type");

    if (lhs.valueType == VALUETYPE::FLOAT)
    {
        DebugLog("<FLAOT> > <FLOAT> detected!......OK");
        return VALUE(lhs.fval > rhs.fval);
    }

    else if (lhs.valueType == VALUETYPE::INT)
    {
        DebugLog("<INT> > <INT> detected!......OK");
        return VALUE(lhs.ival > rhs.ival);
    }

    else
    {
        throw string("Only int and float can do Greater than operation!");
    }
}

VALUE operator>=(const VALUE &lhs, const VALUE &rhs)
{
    // comparation operator must be same value type
    if (lhs.valueType != rhs.valueType)
        throw string("Greater or equal than operation can only work on same value type");

    if (lhs.valueType == VALUETYPE::FLOAT)
    {
        DebugLog("<FLAOT> >= <FLOAT> detected!......OK");
        return VALUE(lhs.fval >= rhs.fval);
    }

    else if (lhs.valueType == VALUETYPE::INT)
    {
        DebugLog("<INT> >= <INT> detected!......OK");
        return VALUE(lhs.ival >= rhs.ival);
    }

    else
    {
        throw string("Only int and float can do Greater or equal than operation!");
    }
}

VALUE operator==(const VALUE &lhs, const VALUE &rhs)
{
    // comparation operator must be same value type
    if (lhs.valueType != rhs.valueType)
        throw string("Equal operation can only work on same value type");

    if (lhs.valueType == VALUETYPE::FLOAT)
    {
        DebugLog("<FLAOT> == <FLOAT> detected!......OK");
        return VALUE(lhs.fval == rhs.fval);
    }

    else if (lhs.valueType == VALUETYPE::INT)
    {
        DebugLog("<INT> == <INT> detected!......OK");
        return VALUE(lhs.ival == rhs.ival);
    }

    else if (lhs.valueType == VALUETYPE::BOOLEAN)
    {
        DebugLog("<BOOLEAN> == <BOOLEAN> detected!......OK");
        return VALUE(lhs.bval == rhs.bval);
    }

    else if (lhs.valueType == VALUETYPE::STRING)
    {
        DebugLog("<STRING> == <STRING> detected!......OK");
        return VALUE(lhs.sval == rhs.sval);
    }

    else if (lhs.valueType == VALUETYPE::CHAR)
    {
        DebugLog("<CHAR> == <CHAR> detected!......OK");
        return VALUE(lhs.cval == rhs.cval);
    }

    else
    {
        throw string("Only int, float, string, char, and boolean can do equal operation!");
    }
}

VALUE operator!=(const VALUE &lhs, const VALUE &rhs)
{
    // comparation operator must be same value type
    if (lhs.valueType != rhs.valueType)
        throw string("Non Equal operation can only work on same value type");

    if (lhs.valueType == VALUETYPE::FLOAT)
    {
        DebugLog("<FLAOT> != <FLOAT> detected!......OK");
        return VALUE(lhs.fval != rhs.fval);
    }

    else if (lhs.valueType == VALUETYPE::INT)
    {
        DebugLog("<INT> != <INT> detected!......OK");
        return VALUE(lhs.ival != rhs.ival);
    }

    else if (lhs.valueType == VALUETYPE::BOOLEAN)
    {
        DebugLog("<BOOLEAN> != <BOOLEAN> detected!......OK");
        return VALUE(lhs.bval != rhs.bval);
    }

    else if (lhs.valueType == VALUETYPE::STRING)
    {
        DebugLog("<STRING> != <STRING> detected!......OK");
        return VALUE(lhs.sval != rhs.sval);
    }

    else if (lhs.valueType == VALUETYPE::CHAR)
    {
        DebugLog("<CHAR> != <CHAR> detected!......OK");
        return VALUE(lhs.cval != rhs.cval);
    }

    else
    {
        throw string("Only int, float, string, char, and boolean can do Non Equal operation!");
    }
}

// unary operators
VALUE VALUE::operator-()
{
    // only float and int value can do minus unary operation
    if (this->valueType == VALUETYPE::INT)
    {
        DebugLog("Value type int is doing MINUS unary operation......OK");
        VALUE answer;
        answer.valueType = VALUETYPE::INT;
        answer.ival = -this->ival;
        return answer;
    }
    if (this->valueType == VALUETYPE::FLOAT)
    {
        DebugLog("Value type float is doing MINUS unary operation......OK");
        VALUE answer;
        answer.valueType = VALUETYPE::FLOAT;
        answer.fval = -this->fval;
        return answer;
    }
    else
    {
        throw string("Only int and float value type can do MINUS unary operation!");
    }
}

VALUE VALUE::operator!()
{
    // only boolean value can do or operation
    if (this->valueType == VALUETYPE::BOOLEAN)
    {
        DebugLog("Value type boolean is doing NOT unary operation......OK");
        VALUE answer;
        answer.valueType = VALUETYPE::BOOLEAN;
        answer.bval = !this->bval;
        return answer;
    }
    else
    {
        throw string("Only boolean value type can do NOT unary operation!");
    }
}

// return value type string
string VALUE::ValueTypeString()
{
    return valueTypeToString(valueType);
}

void VALUE::Dump()
{
    if (valueType == VALUETYPE::INVALID)
    {
        cout << "ValueType -> Invalid\n";
    }
    else if (valueType == VALUETYPE::ARRBOOLEAN)
    {
        cout << "ValueType -> Arr Boolean";
        cout << " | ValueValue -> (";
        for (int i = 0; i < bvals.size(); i++)
        {
            cout << bvals[i];

            if (i != bvals.size() - 1)
                cout << ", ";
            else
                cout << ")";
        }
    }
    else if (valueType == VALUETYPE::ARRCHAR)
    {
        cout << "ValueType -> Arr Char";
        cout << " | ValueValue -> (";
        for (int i = 0; i < cvals.size(); i++)
        {
            cout << cvals[i];

            if (i != cvals.size() - 1)
                cout << ", ";
            else
                cout << ")";
        }
    }
    else if (valueType == VALUETYPE::ARRFLOAT)
    {
        cout << "ValueType -> Arr Double";
        cout << " | ValueValue -> (";
        for (int i = 0; i < fvals.size(); i++)
        {
            cout << fvals[i];

            if (i != fvals.size() - 1)
                cout << ", ";
            else
                cout << ")";
        }
    }
    else if (valueType == VALUETYPE::ARRINT)
    {
        cout << "ValueType -> Arr Integer";
        cout << " | ValueValue -> (";
        for (int i = 0; i < ivals.size(); i++)
        {
            cout << ivals[i];

            if (i != ivals.size() - 1)
                cout << ", ";
            else
                cout << ")";
        }
    }
    else if (valueType == VALUETYPE::ARRSTRING)
    {
        cout << "ValueType -> Arr String";
        cout << " | ValueValue -> (";
        for (int i = 0; i < svals.size(); i++)
        {
            cout << svals[i];

            if (i != svals.size() - 1)
                cout << ", ";
            else
                cout << ")";
        }
    }
    else if (valueType == VALUETYPE::VOID)
    {
        cout << "ValueType -> Void";
    }
    else if (valueType == VALUETYPE::BOOLEAN)
    {
        cout << "ValueType -> Boolean";
        cout << " | ValueValue -> (" << bval << ")";
    }
    else if (valueType == VALUETYPE::CHAR)
    {
        cout << "ValueType -> Char";
        cout << " | ValueValue -> (" << cval << ")";
    }
    else if (valueType == VALUETYPE::FLOAT)
    {
        cout << "ValueType -> Double";
        cout << " | ValueValue -> (" << fval << ")";
    }
    else if (valueType == VALUETYPE::INT)
    {
        cout << "ValueType -> Integer";
        cout << " | ValueValue -> (" << ival << ")";
    }
    else if (valueType == VALUETYPE::STRING)
    {
        cout << "ValueType -> String";
        cout << " | ValueValue -> (" << sval << ")";
    }
}

void Symbol::Dump()
{
    for (int i = 0; i < ids.size(); i++)
    {
        cout << "\n";
        ids[i]->Dump();
        cout << "\n";
    }
}

int Symbol::getScopeIndex(){
    int scopeIndex = 0;
    for(int i=0; i<ids.size() - 1; i++){
        if(ids[i]->value.valueType == VALUETYPE::FLOAT) scopeIndex += 2;
        else scopeIndex += 1;
    }
    return scopeIndex;
}

void SymbolTable::CreateSymbol()
{
    DebugLog("New Symbol Created! Means that we have enter a new scope......OK");
    Symbol newSymbol = Symbol();
    // set the parent id pointer
    ID *parentPtr = NULL;
    if (validSymbols.size() && validSymbols.back().ids.size())
        parentPtr = validSymbols.back().ids.back();

    // check whether the parent pointer is a valid pointer
    if (parentPtr)
    {
        // only function and object id will be used as parent id ptr
        if (parentPtr->idType == IDTYPE::FUNCTION || parentPtr->idType == IDTYPE::OBJECTID)
        {
            newSymbol.parentIDPtr = parentPtr;
        }
    }
    this->validSymbols.push_back(Symbol());
}

void SymbolTable::DropSymbol()
{
    DebugLog("Symbol Dropped! Means that we have leave the current scope......OK");

    Symbol symbol = this->validSymbols.back();
    this->validSymbols.pop_back();
    this->invalidSymbols.push_back(symbol);
}

ID *SymbolTable::LookUp(string IDName)
{
    // look up for the current scope first
    for (int i = validSymbols.size() - 1; i >= 0; i--)
    {
        for (int j = 0; j < validSymbols[i].ids.size(); j++)
        {
            // found same id with the name
            if (IDName == validSymbols[i].ids[j]->IDName)
            {
                return validSymbols[i].ids[j];
            }
        }
    }

    // else look up not found
    throw string("IDName pass in(" + IDName + ") didn't found in symbol table!\n");
}

ID *SymbolTable::Insert(ID *idPtr)
{
    // get the symbol from the current scope
    int i = validSymbols.size() - 1;
    // check whether has same id name inside the current scope
    for (int j = 0; j < validSymbols[i].ids.size(); j++)
    {
        // the id with same name already declare in this scope
        if (validSymbols[i].ids[j]->IDName == idPtr->IDName)
        {
            throw("A same ID name " + validSymbols[i].ids[j]->IDName + " found has already declared in this scope with id type " + IdTypeToString(validSymbols[i].ids[j]->idType));
        }
    }

    validSymbols[i].ids.push_back(idPtr);
    return idPtr;
}

// check whether current scope is global scope
bool SymbolTable::isGlobalScope(string IDName)
{
    // look up for the current scope first
    for (int i = validSymbols.size() - 1; i >= 0; i--)
    {
        for (int j = 0; j < validSymbols[i].ids.size(); j++)
        {
            // found same id with the name
            if (IDName == validSymbols[i].ids[j]->IDName)
            {
                // zero scope should only contain the class name
                // so the first scope is the global scope then
                if (i == 1)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
    }

    // else look up not found
    throw string("IDName pass in(" + IDName + ") didn't found in symbol table!\n");
}

bool SymbolTable::isGlobalScope()
{
    // zero scope should only contain the class name
    // so the first scope is the global scope then (hence the size of valid symbol must be 2)
    if (validSymbols.size() == 2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// get the object name / class name
string SymbolTable::getObjectName()
{
    return validSymbols[0].ids[0]->IDName;
}

void SymbolTable::DumpValidSymbols()
{
    for (int i = 0; i < validSymbols.size(); i++)
    {
        cout << "\n";
        validSymbols[i].Dump();
        cout << "\n";
    }
}

void SymbolTable::DumpInvalidSymbols()
{
    for (int i = 0; i < invalidSymbols.size(); i++)
    {
        cout << "\n";
        invalidSymbols[i].Dump();
        cout << "\n";
    }
}

// init for global variable
string OperandStackManager::globalInit(ID* globalVarID, string objectName){
    // check whether the var type is in our support types
    if(!isValueTypeSupported(globalVarID->value.valueType)){
        yyerror("We only support types int, float, boolean, char. "
        "For initing global variable!\n");
    }

    // field static {type} {class name}.{id name}
    string ret = "field static " + globalVarID->value.ValueTypeString() + " " + globalVarID->IDName;
    return ret;
}

string OperandStackManager::globalInitWithValue(ID* globalVarID, string objectName){
    // check whether the var type is in our support types
    if(!isValueTypeSupported(globalVarID->value.valueType)){
        yyerror("We only support types int, float, boolean, char. "
        "For initing global variable!\n");
    }

    // field static {type} {class name}.{id name}
    string ret = "field static " + 
        globalVarID->value.ValueTypeString() + " " + globalVarID->IDName + " = ";

    // int
    if(globalVarID->value.valueType == VALUETYPE::INT){
        ret += to_string(globalVarID->value.ival);
    }
    // char
    else if(globalVarID->value.valueType == VALUETYPE::CHAR){
        ret += to_string(globalVarID->value.cval);
    }
    // float
    else if(globalVarID->value.valueType == VALUETYPE::FLOAT){
        ret += to_string(globalVarID->value.fval);
    }
    // boolean
    else if(globalVarID->value.valueType == VALUETYPE::BOOLEAN){
        ret += to_string(globalVarID->value.bval ? 1: 0);
    }
    // string
    else if(globalVarID->value.valueType == VALUETYPE::STRING){
        ret += "\"" + globalVarID->value.sval + "\"";
    }

    return ret;
}

// store value from operand stack
string OperandStackManager::globalStore(ID* globalVarID, string objectName){
    // check whether the var type is in our support types
    if(!isValueTypeSupported(globalVarID->value.valueType)){
        yyerror("We only support types int, float, boolean, char. "
        "For storing value from operand stack to global variable!\n");
    }

    // putstatic {type} {className}.{id name}
    string ret = "putstatic " + globalVarID->value.ValueTypeString() + " " + objectName + "." + globalVarID->IDName;
    return ret;
}

string OperandStackManager::localStore(ID* localVarID){
    // check whether the var type is in our support types
    if(!isValueTypeSupported(localVarID->value.valueType)){
        yyerror("We only support types int, float, boolean, char. "
        "For storing value from operand stack to local variable!\n");
    }

    // {type}store {scope index}
    string ret;
    if(localVarID->value.valueType == VALUETYPE::FLOAT){
        ret =  "dstore " + to_string(localVarID->scopeIndex);
    }
    else if(localVarID->value.valueType == VALUETYPE::CHAR
        ||  localVarID->value.valueType == VALUETYPE::BOOLEAN
        ||  localVarID->value.valueType == VALUETYPE::INT){
        ret =  "istore " + to_string(localVarID->scopeIndex); 
    }
    return ret;
}

// load value to operand stack
string OperandStackManager::globalLoad(ID* globalVarID, string objectName){
    // check whether the var type is in our support types
    if(!isValueTypeSupported(globalVarID->value.valueType)){
        yyerror("We only support types int, float, boolean, char. "
        "For loading value from global variable to operand stack!\n");
    }

    // getstatic {type} {className}.{id name}
    string ret = "getstatic " + globalVarID->value.ValueTypeString() + " " + objectName + "." + globalVarID->IDName;
    return ret;
}

string OperandStackManager::localLoad(ID* localVarID){
    // check whether the var type is in our support types
    if(!isValueTypeSupported(localVarID->value.valueType)){
        yyerror("We only support types int, float, boolean, char. "
        "For loading value from local variable to operand stack!\n");
    }

    // {type}load {scope index}
    string ret;
    if(localVarID->value.valueType == VALUETYPE::FLOAT){
        ret =  "dload " + to_string(localVarID->scopeIndex);
    }
    else if(localVarID->value.valueType == VALUETYPE::CHAR
        ||  localVarID->value.valueType == VALUETYPE::BOOLEAN
        ||  localVarID->value.valueType == VALUETYPE::INT){
        ret =  "iload " + to_string(localVarID->scopeIndex); 
    }
    return ret;
}
string OperandStackManager::constantLoad(VALUE* constantValue){
    // check whether the var type is in our support types
    // *** special consideration for string
    if(!isValueTypeSupported(constantValue->valueType) && constantValue->valueType != VALUETYPE::STRING){
        yyerror("We only support types int, float, boolean, char. "
        "For loading value from constant expression to operand stack!\n");
    }

    string ret;
    // sipush 10
    // iconst 1
    // fconst 1.5
    if(constantValue->valueType == VALUETYPE::BOOLEAN){
        ret = "ldc " + to_string(constantValue->bval ? 1: 0);
    }

    else if(constantValue->valueType == VALUETYPE::INT){
        ret = "ldc " + to_string(constantValue->ival);
    }

    else if(constantValue->valueType == VALUETYPE::CHAR){
        ret = "ldc " + to_string(constantValue->cval);
    }

    else if(constantValue->valueType == VALUETYPE::FLOAT){
        ret = "ldc2_w " + to_string(constantValue->fval);
    }

    else if(constantValue->valueType == VALUETYPE::STRING){
        ret = "ldc \"" + constantValue->sval + "\"";
    }

    return ret;
}

void LabelManager::createComparisonLabel(LabelType labelType){
    // push the stack
    LabelManager::pushStack();

    PrintJasmTab();
    switch (labelType)
    {
    case LabelType::LLT:
        fprintf(yyout, "iflt ");
        break;
    case LabelType::LLE:
        fprintf(yyout, "ifle ");
        break;
    case LabelType::LGE:
        fprintf(yyout, "ifge ");
        break;
    case LabelType::LGT:
        fprintf(yyout, "ifgt ");
        break;
    case LabelType::LEQ:
        fprintf(yyout, "ifeq ");
        break;
    case LabelType::LNQ:
        fprintf(yyout, "ifne ");
        break;
    
    default:
        break;
    }
    fprintf(yyout, "%s\n", LabelManager::getLabelString(labelType, LabelState::FALSE).c_str());

    PrintJasmTab();
    fprintf(yyout, "iconst_0\n");

    PrintJasmTab();
    fprintf(yyout, "goto %s\n", LabelManager::getLabelString(labelType, LabelState::EXIT).c_str());

    PrintJasmTab();
    fprintf(yyout, "%s: \n", LabelManager::getLabelString(labelType, LabelState::FALSE).c_str());

    PrintJasmTab();
    fprintf(yyout, "iconst_1\n");

    PrintJasmTab();
    fprintf(yyout, "%s: \n", LabelManager::getLabelString(labelType, LabelState::EXIT).c_str());

    LabelManager::updateCounter(labelType);
    // pop the stack
    LabelManager::popStack();
}

string LabelManager::getOperatorString(Operation operation, VALUETYPE valueType){
    string ret;
    ret += (valueType == VALUETYPE::INT ? "i" : "d");

    switch(operation){
        case Operation::ADD:
            ret += "add"; 
            break;
        case Operation::SUB:
            ret += "sub"; 
            break;
        case Operation::MUL:
            ret += "mul";
            break;
        case Operation::DIV:
            ret += "div";
            break;
        case Operation::REM:
            ret += "rem";
            break;
        case Operation::NEG:
            ret += "neg";
            break;
        default:
            break;
    }
    return ret;
}

string LabelManager::labelTypeString(LabelType labelType){
    switch(labelType){
        case LabelType::LLT:
            return "LT"; 
            break;
        case LabelType::LLE:
            return "LE";
            break;
        case LabelType::LEQ:
            return "EQ";
            break;
        case LabelType::LNQ:
            return "NQ";
            break;
        case LabelType::LGE:
            return "GE";
            break;
        case LabelType::LGT:
            return "GT";
            break;
        case LabelType::LFOR:
            return "FOR";
            break;
        case LabelType::LWHILE:
            return "WHILE";
            break;
        case LabelType::LIF:
            return "IF";
            break;
        default:
            throw "Invalid label Type!\n";
            break;
    }
}

string LabelManager::getLabelString(LabelType labelType, LabelState labelState){
    string ret = "L";

    switch (labelState)
    {
    case LabelState::BEGIN:
        ret += "Begin";
        break;
    case LabelState::TRUE:
        ret += "True";
        break;
    case LabelState::FALSE:
        ret += "False";
        break;
    case LabelState::EXIT:
        ret += "Exit";
        break;
    default:
        break;
    }
    ret += to_string(LabelManager::labelStackCounter.back());

    return ret;
} 

void LabelManager::updateCounter(LabelType labelType){
    // LabelManager::labelCounter++;
    return;
}

// add the label stack counter
void LabelManager::pushStack(){
    LabelManager::labelCounter++;
    LabelManager::labelStackCounter.push_back(LabelManager::labelCounter);
    return;
}

// subtract the label stack counter
void LabelManager::popStack(){
    LabelManager::labelStackCounter.pop_back();
    return;
}

void DebugLog(string log, bool hasLine)
{
    if (isProject2)
    {
        if (hasLine)
            cout << log << '\n';
        else
            cout << log;
    }
}

string IdTypeToString(IDTYPE idtype)
{
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
    case IDTYPE::GLOBALVAR:
        return "Global Variable";
        break;
    case IDTYPE::OBJECTID:
        return "Object";
        break;

    default:
        throw string("ID type provided doesn't found!");
        return "Invalid";
        break;
    }
}

string valueTypeToString(VALUETYPE valueType)
{
    switch (valueType)
    {
    case VALUETYPE::INVALID:
        return "invalid";
        break;
    case VALUETYPE::UNSET:
        return "unset";
        break;
    case VALUETYPE::VOID:
        return "void";
        break;
    case VALUETYPE::STRING:
        return "java.lang.String";
        break;
    case VALUETYPE::CHAR:
        return "char";
        break;
    case VALUETYPE::INT:
        return "int";
        break;
    case VALUETYPE::FLOAT:
        return "double";
        break;
    case VALUETYPE::BOOLEAN:
        return "boolean";
        break;
    case VALUETYPE::ARRSTRING:
        return "arr string";
        break;
    case VALUETYPE::ARRCHAR:
        return "arr char";
        break;
    case VALUETYPE::ARRINT:
        return "arr int";
        break;
    case VALUETYPE::ARRFLOAT:
        return "arr float";
        break;
    case VALUETYPE::ARRBOOLEAN:
        return "arr bool";
        break;

    default:
        throw string("Value Type provided not found!");
        return "Invalid";
        break;
    }
}

// check the value type is supported or not
bool isValueTypeSupported(VALUETYPE valueType)
{
    if (valueType == VALUETYPE::INT ||
        valueType == VALUETYPE::BOOLEAN ||
        valueType == VALUETYPE::CHAR ||
        valueType == VALUETYPE::FLOAT ||
        valueType == VALUETYPE::STRING)
    {
        return true;
    }
    else
    {
        return false;
    }
}