// DBDefence.ConsoleCpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <conio.h>

std::string GetPassword(const std::string prompt, const char maskCharacter) {

    std::string password;
    char consoleInputChar;
    const char ASCII_BACKSPACE = 8;             // TODO: Support backspace (delete)
    const char ASCII_CARRIAGE_RETURN = 13;

    std::cout << prompt;

    while ((consoleInputChar = _getch()) != ASCII_CARRIAGE_RETURN) {
        password += consoleInputChar;
        std::cout << maskCharacter;
    }

    return password;
}

int main(int argc, char* argv[]) {
    std::cout << "Hello World!\n";

    std::string password = GetPassword("\nEnter the password: ", '*');

    std::cout << "\n" << password << "\n";
}