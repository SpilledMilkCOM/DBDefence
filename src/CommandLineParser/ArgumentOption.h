#pragma once

#include <string>

using namespace std;

class ArgumentOption {

private:

    string _description;
    bool _found = false;
    string _option;
    bool _required = false;
    string _value;
    string _valueName;

public:

    ArgumentOption(string option, string valueName, string description, bool required);

    string Description();
    bool Found();
    bool Found(bool found);
    string Option();
    bool Required();
    string Value();
    string Value(string value);
    string ValueName();
};