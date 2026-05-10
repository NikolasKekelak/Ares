//
// Created by nikolas on 5/10/26.
//

#include "ErrorHandler.h"

#include <iostream>
#include <ostream>

#include "../Ares/Ares.h"

std::string ErrorHandler::errorString;

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
    }
    Ares::terminate();
}

void ErrorHandler::setErrorString(const std::string &str) {
    errorString = str;
}
