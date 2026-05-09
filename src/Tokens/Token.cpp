//
// Created by nikolas on 5/7/26.
//

#include "Token.h"

#include <utility>

Token::Token(std::string literal, std::string lexeme, const TokenType type, const int line, const int column) {
    this->literal = std::move(literal);
    this->lexeme = std::move(lexeme);
    this->type = type;
    this->line = line;
    this->column = column;
}

ErrorToken Token::getErrorToken() {
    return {literal, type, line, column};
}

std::string Token::getLiteral() const {
    return literal;
}

std::string Token::getLexeme() const {
    return lexeme;
}

int Token::getLine() const {
    return line;
}

int Token::getColumn() const {
    return column;
}

TokenType Token::getType() const {
    return type;
}
