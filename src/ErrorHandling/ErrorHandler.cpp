//
// Created by nikolas on 5/10/26.
//

#include "ErrorHandler.h"

#include <iostream>
#include <ostream>

#include "../Ares/Ares.h"

std::string ErrorHandler::errorString;
ErrorToken ErrorHandler::errorToken;

void ErrorHandler::handleError(ErrorCode code) {
    std::cout << "\033[31m" << "ares: error: " << "\033[0m";
    switch (code) {
        case MISSING_ARGUMENT_AFTER_OUTPUT_FLAG:
            std::cout << "missing argument for filename after '-o' flag" << std::endl;
            break;
        case UNKNOWN_FLAG_ENCOUNTERED:
            std::cout <<" unknown flag encountered: "<< errorString << std::endl;
            break;
        case FILE_NOT_FOUND:
            std::cout << "file not found: " << errorString << std::endl;
            break;
        case SYNTAX_ERROR:
            std::cout << "syntax error: " << errorString << " "<< errorToken.line << "." << errorToken.column<<std::endl;
            showcase(errorToken.file, errorToken);
            break;
        case UNDEFINED_VARIABLE:
            std::cout << "'" << errorString << "' variable was not defined" << std::endl;
            break;
        default: std::cout<< code << " " << errorString;
            break;
    }
    Ares::terminate();
}

void ErrorHandler::setErrorString(const std::string &str) {
    errorString = str;
}

void ErrorHandler::setErrorToken(ErrorToken &token) {
    errorToken = token;
}
