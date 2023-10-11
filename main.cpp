#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <windows.h>

#define FOREGROUND_MAGENTA 0
#define FOREGROUND_YELLOW 0

void SetColor(int color) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, color);
}

int main() {
    std::ifstream inFile("input.txt");
    std::ofstream outFile("out.txt");

    if (!inFile.is_open()) {
        std::cerr << "Error opening input.txt" << std::endl;
        return 1;
    }

    // Define regex patterns for each token class
    std::regex numberRgx("(-?\\d+\\.\\d+|-?\\d+|0x[0-9a-fA-F]+)");
    std::regex stringRgx("\"[^\"]*\"");
    std::regex charRgx("'.'");
    std::regex preprocessorRgx("#include <[a-zA-Z_][a-zA-Z0-9_\\.]*>");
    std::regex commentRgx("//[^\n]*");
    std::regex reservedWordsRgx("\\b(int|double|float|char|return)\\b");
    std::regex operatorsRgx("(\\+|-|\\*|/|%)");
    std::regex punctuationRgx("[;\\(\\){}\\.]");
    std::regex identifierRgx("[a-zA-Z_][a-zA-Z0-9_]*");

    std::string line;
    while (std::getline(inFile, line)) {
        outFile << line << std::endl;

        std::smatch match;

        std::regex_search(line, match, numberRgx);
        if (!match.str().empty()) {
            SetColor(FOREGROUND_GREEN);
            std::cout << "<" << match.str() << ", number>" << std::endl;
        }

        std::regex_search(line, match, stringRgx);
        if (!match.str().empty()) {
            SetColor(FOREGROUND_BLUE);
            std::cout << "<" << match.str() << ", string>" << std::endl;
        }

        std::regex_search(line, match, charRgx);
        if (!match.str().empty()) {
            SetColor(FOREGROUND_BLUE);
            std::cout << "<" << match.str() << ", char>" << std::endl;
        }

        std::regex_search(line, match, preprocessorRgx);
        if (!match.str().empty()) {
            SetColor(FOREGROUND_RED);
            std::cout << "<" << match.str() << ", preprocessor>" << std::endl;
        }

        std::regex_search(line, match, commentRgx);
        if (!match.str().empty()) {
            SetColor(FOREGROUND_MAGENTA);
            std::cout << "<" << match.str() << ", comment>" << std::endl;
        }

        std::regex_search(line, match, reservedWordsRgx);
        if (!match.str().empty()) {
            SetColor(FOREGROUND_YELLOW);
            std::cout << "<" << match.str() << ", reserved word>" << std::endl;
        }

        std::regex_search(line, match, operatorsRgx);
        if (!match.str().empty()) {
            SetColor(FOREGROUND_RED | FOREGROUND_GREEN);
            std::cout << "<" << match.str() << ", operator>" << std::endl;
        }

        std::regex_search(line, match, punctuationRgx);
        if (!match.str().empty()) {
            SetColor(FOREGROUND_BLUE | FOREGROUND_GREEN);
            std::cout << "<" << match.str() << ", punctuation>" << std::endl;
        }

        std::regex_search(line, match, identifierRgx);
        if (!match.str().empty()) {
            SetColor(FOREGROUND_INTENSITY);
            std::cout << "<" << match.str() << ", identifier>" << std::endl;
        }

        SetColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }

    inFile.close();
    outFile.close();
    return 0;
}
