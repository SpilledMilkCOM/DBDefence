#include <iostream>

#include "LoggerStdOut.h"

LoggerStdOut::LoggerStdOut() {
}

void LoggerStdOut::Log(string message) {
    cout << message << "\n";
}

void LoggerStdOut::Log(wstring message) {
    wcout << message << L"\n";
}