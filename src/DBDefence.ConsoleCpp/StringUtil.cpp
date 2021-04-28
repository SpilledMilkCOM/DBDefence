#include <string>
#include <codecvt>
#include <locale>

#include "StringUtil.h"

// Function comments are in the header file. (hover over the function name for help text)

string ConvertToString(wstring source) {
    return wstring_convert<codecvt_utf8<wchar_t>>().to_bytes(source);
}

wchar_t* ConvertToWideCharT(string source) {
    return ConvertToWideCharT(ConvertToWideString(source).c_str());
}

wchar_t* ConvertToWideCharT(wstring source) {
    return _wcsdup(source.c_str());
}

wstring ConvertToWideString(string source) {
    return wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(source);
}