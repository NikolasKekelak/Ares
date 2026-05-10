//
// Created by nikolas on 5/10/26.
//

#ifndef ARES_ERRORHANDLER_H
#define ARES_ERRORHANDLER_H
#include <string>


enum ErrorCode {
    // Arg parsing error
    MISSING_ARGUMENT_AFTER_OUTPUT_FLAG,
    UNKNOWN_FLAG_ENCOUNTERED,
    FILE_NOT_FOUND,
    // Lexer error
    UNKNOWN_CHARACTER_ENCOUNTERED

};

class ErrorHandler {
    static std::string errorString;
public:
    static void handleError(ErrorCode);
    static void setErrorString(const std::string& str);
};



#endif //ARES_ERRORHANDLER_H
