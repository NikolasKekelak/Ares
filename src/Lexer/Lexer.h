//
// Created by nikolas on 5/7/26.
//

#ifndef ARES_LEXER_H
#define ARES_LEXER_H
#include <string>
#include <unordered_map>
#include <vector>
#include "../Tokens/Token.h"

class Token;


class Lexer {
    std::string source;
    std::string sourceFile;
    std::vector<Token> tokens;

    // couple of fields to keep track of where the scanner is in the source code.
    int start = 0;
    int current = 0;

    int line = 1;
    int column = 0;


    std::unordered_map<std::string, TokenType> keywords = {
        {"if", TK_IF},
        {"else", TK_ELSE},
        {"while", TK_WHILE},
        {"for", TK_FOR},
        {"return", TK_RETURN},
        {"break", TK_BREAK},
        {"continue", TK_CONTINUE},
        {"true", TK_TRUE},
        {"false", TK_FALSE},
        {"switch", TK_SWITCH},
        {"case", TK_CASE},
        {"default", TK_DEFAULT},
        {"NULL", TK_NULL},
        {"static", TK_STATIC},
        {"private", TK_PRIVATE},
        {"local", TK_LOCAL},
        {"global", TK_GLOBAL},
        {"async", TK_ASYNC},
        {"atomic", TK_ATOMIC},
        {"void", TK_VOID},

        {"long" , TK_INT},  //8 bytes
        {"int", TK_INT},    //4 bytes
        {"short", TK_INT},  //2 bytes

        {"bool", TK_BOOL},   //1 byte
        {"char", TK_CHAR},
        {"string", TK_STRING},
        {"float", TK_FLOAT},
        {"out", TK_STDOUT},
        {"in", TK_STDIN}

    };

    bool isAtEnd() const;

    void scanToken();

    char advance();

    void addToken(TokenType type);

    void addToken(TokenType type, const std::string& literal);

    bool match(char expected);

    char peekNext() const;

    void _number();
    void _char();
    void _string();
    void _identifier();
    void _comment();
public:
    void scanTokens();
    std::vector<Token>& getTokens();
    void setSource(std::string source);

};
#endif