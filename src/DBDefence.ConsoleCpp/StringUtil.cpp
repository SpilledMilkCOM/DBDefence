#include <string>
#include <codecvt>
#include <locale>

#include "StringUtil.h"

std::string ConvertToString(std::wstring source) {
    return std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(source);
}

wchar_t* ConvertToWideCharT(std::string source) {
    return ConvertToWideCharT(ConvertToWideString(source).c_str());
}

wchar_t* ConvertToWideCharT(std::wstring source) {
    return _wcsdup(source.c_str());
}

std::wstring ConvertToWideString(std::string source) {
    return std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(source);
}