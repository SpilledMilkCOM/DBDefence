#pragma once

#include <string>

using namespace std;

/// <summary>
/// Converts a wide string to a string
/// </summary>
/// <param name="source">string to convert</param>
/// <returns>string (char based basic_string object)</returns>
string ConvertToString(wstring source);

/// <summary>
/// Converts a string to a wide char type pointer
/// </summary>
/// <param name="source">string to convert</param>
/// <returns>wide char pointer - needs to be free()'d</returns>
wchar_t* ConvertToWideCharT(string source);

/// <summary>
/// Converts a wide string to a wide char type pointer
/// </summary>
/// <param name="source">string to convert</param>
/// <returns>wide char pointer - needs to be free()'d</returns>
wchar_t* ConvertToWideCharT(wstring source);

/// <summary>
/// Converts a string to a wide string
/// </summary>
/// <param name="source">string to convert</param>
/// <returns>wide string (wchar_t based basic_string object)</returns>
wstring ConvertToWideString(string source);