#include"project2.h"

// extern variables for lex
extern int yylineno;
extern char* yytext;

// extern variables for line
extern string lineBuffer;
extern int yylineno;  // defined and maintained in lex

// extern variables for yacc
int yyerror(const char* );

// output the current line buffer
void AddList(char* token){
    lineBuffer += string(token);
}

void ListLine(){
    yylineno++;
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

ID::ID(string idName)
{
    // set the id type
    idType = IDTYPE::INVALID;

    this->IDName = idName;
}

void ID::SetToFunction()
{
    idType = IDTYPE::FUNCTION;
    retVal.valueType = VALUETYPE::UNSET;
}

void ID::SetToConstVar()
{
    idType = IDTYPE::CONSTVAR;
    value.valueType = VALUETYPE::UNSET;
}

void ID::SetToVar()
{
    idType = IDTYPE::VARIABLE;
    value.valueType = VALUETYPE::UNSET;
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
        }
        // error handling as the value value type must be unset 
        else {
            yyerror("Error found in the function of SetValueType\nID's value type must be unset!!!\n");
        }
    }
    else {
        yyerror("Error found in the function of SetValueType\nID type must be constvar or var!!!\n");
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
        }
        // error handling as the value value type must be unset 
        else {
            yyerror("Error found in the function of SetReturnType\nID's return value type must be unset!!!\n");
        }
    }
    else {
        yyerror("Error found in the function of SetReturnType\nID type must be function!!!\n");
    }
}

// push back parameter for the function
void ID::AddParameter(ID id)
{
    this->parameters.push_back(new ID(id));
}

void ID::SetConstValue(char cval)
{
    // id checking
    if (idType == IDTYPE::CONSTVAR) {
        // set the value type implicitly
        if (value.valueType == VALUETYPE::UNSET) {
            value.valueType == VALUETYPE::CHAR;
        }

        // set the value
        if (value.valueType != VALUETYPE::CHAR)
        {
            value.cval = cval;
        }
        else {
            yyerror("Error found in the function of SetConstValue(char cval)\nValue's value type must be char!!!\n");
        }
    }
    else {
        yyerror("Error found in the function of SetConstValue(char cval)\nID type must be const var!!!\n");
    }
}

void ID::SetConstValue(double fval) {
    // id checking
    if (idType == IDTYPE::CONSTVAR) {
        // set the value type implicitly
        if (value.valueType == VALUETYPE::UNSET) {
            value.valueType == VALUETYPE::FLOAT;
        }

        // set the value
        if (value.valueType != VALUETYPE::FLOAT)
        {
            value.fval = fval;
        }
        else {
            yyerror("Error found in the function of SetConstValue(double fval)\nValue's value type must be double!!!\n");
        }
    }
    else {
        yyerror("Error found in the function of SetConstValue(double fval)\nID type must be const var!!!\n");
    }
}

void ID::SetConstValue(string sval) {
    // id checking
    if (idType == IDTYPE::CONSTVAR) {
        // set the value type implicitly
        if (value.valueType == VALUETYPE::UNSET) {
            value.valueType == VALUETYPE::STRING;
        }

        // set the value
        if (value.valueType != VALUETYPE::STRING)
        {
            value.sval = sval;
        }
        else {
            yyerror("Error found in the function of SetConstValue(string sval)\nValue's value type must be string!!!\n");
        }
    }
    else {
        yyerror("Error found in the function of SetConstValue(string sval)\nID type must be const var!!!\n");
    }
}

void ID::SetConstValue(int ival) {
    // id checking
    if (idType == IDTYPE::CONSTVAR) {
        // set the value type implicitly
        if (value.valueType == VALUETYPE::UNSET) {
            value.valueType == VALUETYPE::INT;
        }

        // set the value
        if (value.valueType != VALUETYPE::INT)
        {
            value.ival = ival;
        }
        else {
            yyerror("Error found in the function of SetConstValue(int ival)\nValue's value type must be int!!!\n");
        }
    }
    else {
        yyerror("Error found in the function of SetConstValue(int ival)\nID type must be const var!!!\n");
    }
}

void ID::SetConstValue(vector<char> cvals) {
    // id checking
    if (idType == IDTYPE::CONSTVAR) {
        // set the value type implicitly
        if (value.valueType == VALUETYPE::UNSET) {
            value.valueType == VALUETYPE::ARRCHAR;
        }

        // set the value
        if (value.valueType != VALUETYPE::ARRCHAR)
        {
            value.cvals = cvals;
        }
        else {
            yyerror("Error found in the function of SetConstValue(vector<char> cvals)\nValue's value type must be char array!!!\n");
        }
    }
    else {
        yyerror("Error found in the function of SetConstValue(vector<char> cvals)\nID type must be const var!!!\n");
    }
}

void ID::SetConstValue(vector<double> dvals) {
    // id checking
    if (idType == IDTYPE::CONSTVAR) {
        // set the value type implicitly
        if (value.valueType == VALUETYPE::UNSET) {
            value.valueType == VALUETYPE::ARRFLOAT;
        }

        // set the value
        if (value.valueType != VALUETYPE::ARRFLOAT)
        {
            value.dvals = dvals;
        }
        else {
            yyerror("Error found in the function of SetConstValue(vector<double> dvals)\nValue's value type must be double array!!!\n");
        }
    }
    else {
        yyerror("Error found in the function of SetConstValue(vector<double> dvals)\nID type must be const var!!!\n");
    }
}

void ID::SetConstValue(vector<string> svals) {
    // id checking
    if (idType == IDTYPE::CONSTVAR) {
        // set the value type implicitly
        if (value.valueType == VALUETYPE::UNSET) {
            value.valueType == VALUETYPE::ARRSTRING;
        }

        // set the value
        if (value.valueType != VALUETYPE::ARRSTRING)
        {
            value.svals = svals;
        }
        else {
            yyerror("Error found in the function of SetConstValue(vector<string> svals)\nValue's value type must be string array!!!\n");
        }
    }
    else {
        yyerror("Error found in the function of SetConstValue(vector<string> svals)\nID type must be const var!!!\n");
    }
}

void ID::SetConstValue(vector<int> ivals)
{
    // id checking
    if (idType == IDTYPE::CONSTVAR) {
        // set the value type implicitly
        if (value.valueType == VALUETYPE::UNSET) {
            value.valueType == VALUETYPE::ARRINT;
        }

        // set the value
        if (value.valueType != VALUETYPE::ARRINT)
        {
            value.ivals = ivals;
        }
        else {
            yyerror("Error found in the function of SetConstValue(vector<int> ivals)\nValue's value type must be int array!!!\n");
        }
    }
    else {
        yyerror("Error found in the function of SetConstValue(vector<int> ivals)\nID type must be const var!!!\n");
    }
}

void ID::SetValue(char cval) {
    // id checking
    if (idType == IDTYPE::VARIABLE) {
        // set the value type implicitly
        if (value.valueType == VALUETYPE::UNSET) {
            value.valueType == VALUETYPE::CHAR;
        }

        // set the value
        if (value.valueType != VALUETYPE::CHAR)
        {
            value.cval = cval;
        }
        else {
            yyerror("Error found in the function of SetValue(char cval)\nValue's value type must be char!!!\n");
        }
    }
    else {
        yyerror("Error found in the function of SetValue(char cval)\nID type must be var!!!\n");
    }
}

void ID::SetValue(double fval) {
    // id checking
    if (idType == IDTYPE::VARIABLE) {
        // set the value type implicitly
        if (value.valueType == VALUETYPE::UNSET) {
            value.valueType == VALUETYPE::FLOAT;
        }

        // set the value
        if (value.valueType != VALUETYPE::FLOAT)
        {
            value.fval = fval;
        }
        else {
            yyerror("Error found in the function of SetValue(double fval)\nValue's value type must be double!!!\n");
        }
    }
    else {
        yyerror("Error found in the function of SetValue(double fval)\nID type must be var!!!\n");
    }
}

void ID::SetValue(string sval) {
    // id checking
    if (idType == IDTYPE::VARIABLE) {
        // set the value type implicitly
        if (value.valueType == VALUETYPE::UNSET) {
            value.valueType == VALUETYPE::STRING;
        }

        // set the value
        if (value.valueType != VALUETYPE::STRING)
        {
            value.sval = sval;
        }
        else {
            yyerror("Error found in the function of SetValue(string sval)\nValue's value type must be string!!!\n");
        }
    }
    else {
        yyerror("Error found in the function of SetValue(string sval)\nID type must be var!!!\n");
    }
}

void ID::SetValue(int ival) {
    // id checking
    if (idType == IDTYPE::VARIABLE) {
        // set the value type implicitly
        if (value.valueType == VALUETYPE::UNSET) {
            value.valueType == VALUETYPE::INT;
        }

        // set the value
        if (value.valueType != VALUETYPE::INT)
        {
            value.ival = ival;
        }
        else {
            yyerror("Error found in the function of SetValue(int ival)\nValue's value type must be int!!!\n");
        }
    }
    else {
        yyerror("Error found in the function of SetValue(int ival)\nID type must be var!!!\n");
    }
}

void ID::SetValue(vector<char> cvals) {
    // id checking
    if (idType == IDTYPE::VARIABLE) {
        // set the value type implicitly
        if (value.valueType == VALUETYPE::UNSET) {
            value.valueType == VALUETYPE::ARRCHAR;
        }

        // set the value
        if (value.valueType != VALUETYPE::ARRCHAR)
        {
            value.cvals = cvals;
        }
        else {
            yyerror("Error found in the function of SetValue(vector<char> cvals)\nValue's value type must be char array!!!\n");
        }
    }
    else {
        yyerror("Error found in the function of SetValue(vector<char> cvals)\nID type must be var!!!\n");
    }
}

void ID::SetValue(vector<double> dvals) {
    // id checking
    if (idType == IDTYPE::VARIABLE) {
        // set the value type implicitly
        if (value.valueType == VALUETYPE::UNSET) {
            value.valueType == VALUETYPE::ARRFLOAT;
        }

        // set the value
        if (value.valueType != VALUETYPE::ARRFLOAT)
        {
            value.dvals = dvals;
        }
        else {
            yyerror("Error found in the function of SetValue(vector<double> dvals)\nValue's value type must be double array!!!\n");
        }
    }
    else {
        yyerror("Error found in the function of SetValue(vector<double> dvals)\nID type must be var!!!\n");
    }
}

void ID::SetValue(vector<string> svals) {
    // id checking
    if (idType == IDTYPE::VARIABLE) {
        // set the value type implicitly
        if (value.valueType == VALUETYPE::UNSET) {
            value.valueType == VALUETYPE::ARRSTRING;
        }

        // set the value
        if (value.valueType != VALUETYPE::ARRSTRING)
        {
            value.svals = svals;
        }
        else {
            yyerror("Error found in the function of SetValue(vector<string> svals)\nValue's value type must be string array!!!\n");
        }
    }
    else {
        yyerror("Error found in the function of SetValue(vector<string> svals)\nID type must be var!!!\n");
    }
}

void ID::SetValue(vector<int> ivals) {
    // id checking
    if (idType == IDTYPE::VARIABLE) {
        // set the value type implicitly
        if (value.valueType == VALUETYPE::UNSET) {
            value.valueType == VALUETYPE::ARRINT;
        }

        // set the value
        if (value.valueType != VALUETYPE::ARRINT)
        {
            value.ivals = ivals;
        }
        else {
            yyerror("Error found in the function of SetValue(vector<int> ivals)\nValue's value type must be int array!!!\n");
        }
    }
    else {
        yyerror("Error found in the function of SetValue(vector<int> ivals)\nID type must be var!!!\n");
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
        for (int i = 0; i < dvals.size(); i++) {
            cout << dvals[i];

            if (i != dvals.size() - 1)  cout << ", ";
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

ID SymbolTable::LookUp(string IDName)
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
    yyerror("Error found in function SymbolTable::LookUp(string IDName)\nIDName pass in didn't found in symbol table!\n");
    return ID();
}

void SymbolTable::Insert(ID id)
{
    int i = validSymbols.size() - 1;
    validSymbols[i].ids.push_back(id);
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

void DebugLog(string log){
    cout << log << '\n';
}
