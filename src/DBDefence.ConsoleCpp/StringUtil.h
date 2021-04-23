#pragma once

#include <string>

/// <summary>
/// Converts a wide string to a string
/// </summary>
/// <param name="source">string to convert</param>
/// <returns>string (char based basic_string object)</returns>
std::string ConvertToString(std::wstring source);

/// <summary>
/// Converts a string to a wide char type pointer
/// </summary>
/// <param name="source">string to convert</param>
/// <returns>wide char - needs to be free()'d</returns>
wchar_t* ConvertToWideCharT(std::string source);

/// <summary>
/// Converts a wide string to a wide char type pointer
/// </summary>
/// <param name="source">string to convert</param>
/// <returns>wide char - needs to be free()'d</returns>
wchar_t* ConvertToWideCharT(std::wstring source);

/// <summary>
/// Converts a string to a wide string
/// </summary>
/// <param name="source">string to convert</param>
/// <returns>wide string (wchar_t based basic_string object)</returns>
std::wstring ConvertToWideString(std::string source);