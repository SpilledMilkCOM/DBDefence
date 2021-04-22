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