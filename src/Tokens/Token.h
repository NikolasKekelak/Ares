//
// Created by nikolas on 5/7/26.
//

#ifndef ARES_TOKEN_H
#define ARES_TOKEN_H
#include <iostream>
#include <ostream>
#include <string>
#include "../myHeaders.h"

enum TokenType {
    TK_EOF, TK_EOL,

    TK_LEFT_PAREN, TK_RIGHT_PAREN, // ()
    TK_LEFT_BRACE, TK_RIGHT_BRACE, // {}
    TK_LEFT_SQUARE, TK_RIGHT_SQUARE, // []

    TK_PLUS, TK_MINUS, TK_STAR, TK_SLASH, TK_PERCENT, // +,-,*,/,%
    TK_LEFT_SHIFT, TK_RIGHT_SHIFT, // >>,<<

    TK_GREATER, TK_LESS, TK_GREATER_EQUAL, TK_LESS_EQUAL,
    TK_EQUAL, TK_NOT_EQUAL, TK_ASSIGN, TK_NOT,

    TK_AND, TK_OR, // AND, OR

    TK_IDENTIFIER, TK_LITERAL, TK_NUMBER, TK_CHAR_LITERAL,
    TK_INT, TK_FLOAT, TK_CHAR, TK_BOOL, TK_STRING,

    TK_STRUCT, TK_CLASS,

    TK_DOT, TK_COLON, TK_COMMA, TK_SEMICOLON,
    TK_DOUBLE_COLON,

    //KEYWORD STUFF
    TK_IF, TK_ELSE, TK_WHILE, TK_FOR, TK_BREAK, TK_CONTINUE, TK_RETURN,
    TK_TRUE, TK_FALSE, TK_SWITCH, TK_CASE, TK_DEFAULT, TK_NULL,
    TK_STATIC, TK_PUBLIC, TK_PRIVATE,

    TK_LOCAL, TK_GLOBAL, TK_ASYNC, TK_ATOMIC, TK_VOID,

    TK_STDIN, TK_STDOUT, TK_STDERR,

    TK_MAIN,

    TK_UNKNOWN
};

inline std::string getToken(TokenType name) {
    switch (name) {
        case TK_EOF: return "TK_EOF";
        case TK_EOL: return "TK_EOL";
        case TK_LEFT_PAREN: return "TK_LEFT_PAREN";
        case TK_RIGHT_PAREN: return "TK_RIGHT_PAREN";
        case TK_LEFT_BRACE: return "TK_LEFT_BRACE";
        case TK_RIGHT_BRACE: return "TK_RIGHT_BRACE";
        case TK_LEFT_SQUARE: return "TK_LEFT_SQUARE";
        case TK_RIGHT_SQUARE: return "TK_RIGHT_SQUARE";
        case TK_PLUS: return "TK_PLUS";
        case TK_MINUS: return "TK_MINUS";
        case TK_STAR: return "TK_STAR";
        case TK_SLASH: return "TK_SLASH";
        case TK_PERCENT: return "TK_PERCENT";
        case TK_LEFT_SHIFT: return "TK_LEFT_SHIFT";
        case TK_RIGHT_SHIFT: return "TK_RIGHT_SHIFT";
        case TK_GREATER: return "TK_GREATER";
        case TK_LESS: return "TK_LESS";
        case TK_GREATER_EQUAL: return "TK_GREATER_EQUAL";
        case TK_LESS_EQUAL: return "TK_LESS_EQUAL";
        case TK_ASSIGN: return "TK_ASSIGN";
        case TK_NOT: return "TK_NOT";
        case TK_AND: return "TK_AND";
        case TK_OR: return "TK_OR";
        case TK_IDENTIFIER: return "TK_IDENTIFIER";
        case TK_LITERAL: return "TK_LITERAL";
        case TK_STRUCT: return "TK_STRUCT";
        case TK_CLASS: return "TK_CLASS";
        case TK_DOT: return "TK_DOT";
        case TK_COLON: return "TK_COLON";
        case TK_COMMA: return "TK_COMMA";
        case TK_SEMICOLON: return "TK_SEMICOLON";
        case TK_DOUBLE_COLON: return "TK_DOUBLE_COLON";
        case TK_IF: return "TK_IF";
        case TK_ELSE: return "TK_ELSE";
        case TK_WHILE: return "TK_WHILE";
        case TK_FOR: return "TK_FOR";
        case TK_BREAK: return "TK_BREAK";
        case TK_CONTINUE: return "TK_CONTINUE";
        case TK_RETURN: return "TK_RETURN";
        case TK_TRUE: return "TK_TRUE";
        case TK_FALSE: return "TK_FALSE";
        case TK_SWITCH: return "TK_SWITCH";
        case TK_CASE: return "TK_CASE";
        case TK_DEFAULT: return "TK_DEFAULT";
        case TK_NULL: return "TK_NULL";
        case TK_PUBLIC: return "TK_PUBLIC";
        case TK_PRIVATE: return "TK_PRIVATE";
        case TK_ASYNC: return "TK_ASYNC";
        case TK_ATOMIC: return "TK_ATOMIC";
        case TK_GLOBAL: return "TK_GLOBAL";
        case TK_LOCAL: return "TK_LOCAL";
        case TK_VOID: return "TK_VOID";
        case TK_STDIN: return "TK_STDIN";
        case TK_STDOUT: return "TK_STDOUT";
        case TK_STDERR: return "TK_STDERR";
        case TK_MAIN: return "TK_MAIN";
        case TK_INT: return "TK_INT";
        case TK_NUMBER: return "TK_NUMBER";
        case TK_STRING: return "TK_STRING";
        case TK_CHAR: return "TK_CHAR";
        case TK_CHAR_LITERAL: return "TK_CHAR_LITERAL";
        default: TODO("Unknown token");
            return "";
    }
}

struct ErrorToken {
    std::string literal;
    TokenType type;
    int line;
    int column;
};

class Token {
    std::string literal;
    std::string lexeme;
    int line;
    int column;
    TokenType type;

public:
    Token(std::string literal, std::string lexeme, TokenType type, int line, int column);

    Token() {
    };

    ErrorToken getErrorToken();

    [[nodiscard]] std::string getLiteral() const;

    [[nodiscard]] std::string getLexeme() const;

    [[nodiscard]] int getLine() const;

    [[nodiscard]] int getColumn() const;

    [[nodiscard]] TokenType getType() const;

    void print() {
        std::cout << getToken(type);
        if (lexeme!="") {
            std::cout << "(" << lexeme << ")";
        }
        std::cout << std::endl;
    }
};


#endif //NEVIEM_TOKEN_H
