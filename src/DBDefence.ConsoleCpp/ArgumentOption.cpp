#include "ArgumentOption.h"

//----==== CONSTRUCTOR(S) / DESTRUCTOR(S) ====-----------------------------------------------------

ArgumentOption::ArgumentOption(string option, string valueName, string description, bool required) {
    _option = option;
    _description = description;
    _required = required;
    _valueName = valueName;
}

//----==== PROPERTIES ====-------------------------------------------------------------------------

string
ArgumentOption::Description() {
    return _description;
}

string
ArgumentOption::Option() {
    return _option;
}

bool
ArgumentOption::Required() {
    return _required;
}

string
ArgumentOption::Value() {
    return _value;
}

string
ArgumentOption::Value(string value) {
    string result = _value;

    _value = value;

    return result;
}

string
ArgumentOption::ValueName() {
    return _valueName;
}