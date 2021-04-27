#pragma once

#include <string>

using namespace std;

class ArgumentOption {

private:

    string _description;
    bool _found;
    string _option;
    bool _required;
    string _value;
    string _valueName;

public:

    ArgumentOption(string option, string valueName, string description, bool required);

    string Description();
    bool HasOption(string option);
    string Option();
    bool Required();
    string Value();
    string Value(string value);
    string ValueName();
};