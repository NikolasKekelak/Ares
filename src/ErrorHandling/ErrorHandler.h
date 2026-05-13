#pragma once
//
// Created by nikolas on 5/10/26.
//

#ifndef ARES_ERRORHANDLER_H
#define ARES_ERRORHANDLER_H
#include <string>
#include "../Tokens/Token.h"

struct ErrorToken;

enum ErrorCode {
    // Arg parsing error
    MISSING_ARGUMENT_AFTER_OUTPUT_FLAG,
    UNKNOWN_FLAG_ENCOUNTERED,
    FILE_NOT_FOUND,
    SYNTAX_ERROR,
    UNDEFINED_VARIABLE,
    // Lexer error
    UNKNOWN_CHARACTER_ENCOUNTERED

};

inline void showcase(std::string fileName, ErrorToken token) {
    int e_line = token.line;
    int e_column = token.column;

    int length = token.literal.length();
    std::string line ;
    std::ifstream file(fileName);
    int lineCount = 0;

    while (lineCount < e_line) {
        std::getline(file, line);
        lineCount++;
    }
    std::cout << line << std::endl;
    for (int i = 0; i < e_column; i++) { std::cout << " ";}
    for (int i = 0; i < length; i++) { std::cout << "^";}
    file.close();
}

class ErrorHandler {
    static std::string errorString;
    static ErrorToken errorToken;

public:
    static void handleError(ErrorCode);

    static void setErrorString(const std::string& str);
    static void setErrorToken(ErrorToken& token);
};



#endif //ARES_ERRORHANDLER_H
