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
        {"BREAK", TK_BREAK},
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
        {"main", TK_MAIN},
        {"int", TK_INT},
        {"bool", TK_BOOL},
        {"char", TK_CHAR},
        {"string", TK_STRING},
        {"float", TK_FLOAT},

        {"printf", TK_STDIN},
        {"scanf", TK_STDOUT},
        {"stderr", TK_STDERR}

    };

    bool isAtEnd();

    void scanToken();

    char advance();

    void addToken(TokenType type);

    void addToken(TokenType type, std::string literal);

    bool match(char expected);

    char peekNext();

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