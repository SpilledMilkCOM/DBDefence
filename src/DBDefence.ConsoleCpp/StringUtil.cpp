#include <string>
#include <codecvt>
#include <locale>

std::string ConvertToString(std::wstring source) {
    return std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(source);
}

std::wstring ConvertToWideString(std::string source) {
    return std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(source);
}