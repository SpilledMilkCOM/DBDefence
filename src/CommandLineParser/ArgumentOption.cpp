#include "pch.h"

#include "ArgumentOption.h"

//----==== CONSTRUCTOR(S) / DESTRUCTOR(S) ====-----------------------------------------------------

ArgumentOption::ArgumentOption(string option, string valueName, string description, bool required) {
    _option = option;
    _description = description;
    _required = required;
    _valueName = valueName;

    _found = false;
}

//----==== PROPERTIES ====-------------------------------------------------------------------------

string
ArgumentOption::Description() {
    return _description;
}

bool
ArgumentOption::Found() {
    return _found;
}

bool
ArgumentOption::Found(bool found) {
    bool result = _found;

    _found = found;

    return result;
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