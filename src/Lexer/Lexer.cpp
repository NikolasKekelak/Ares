//
// Created by nikolas on 5/7/26.
//

#include "Lexer.h"
#include "../myHeaders.h"

void Lexer::scanTokens() {
    while (!isAtEnd()) {
        start = current;
        scanToken();
    }
    tokens.emplace_back("", "", TK_EOF, line, column);
}

std::vector<Token>& Lexer::getTokens() {
    return tokens;
}

void Lexer::setSource(std::string source) {
    this->source = std::move(source);
}

void Lexer::scanToken() {
    char c = advance();
    switch (c) {
        case '(': addToken(TK_LEFT_PAREN);
            break;
        case ')': addToken(TK_RIGHT_PAREN);
            break;
        case '{': addToken(TK_LEFT_BRACE);
            break;
        case '}': addToken(TK_RIGHT_BRACE);
            break;
        case '[': addToken(TK_LEFT_SQUARE);
            break;
        case ']': addToken(TK_RIGHT_SQUARE);
            break;

        case '+': addToken(TK_PLUS);
            break;
        case '-': addToken(TK_MINUS);
            break;
        case '*': addToken(TK_STAR);
            break;
        case '/': if (match('/')) {
            _comment();
            break;
        }
            addToken(TK_SLASH);
            break;
        case '%': addToken(TK_PERCENT);
            break;
        case '>': addToken(match('=') ? TK_GREATER_EQUAL : match('>') ? TK_RIGHT_SHIFT : TK_GREATER
            );
            break;
        case '<': addToken(match('=') ? TK_LESS_EQUAL : match('<') ? TK_LEFT_SHIFT : TK_LESS
            );
            break;
        case '=': addToken(match('=') ? TK_EQUAL : TK_ASSIGN);
            break;
        case '!': addToken(match('=') ? TK_NOT_EQUAL : TK_NOT);
            break;


        case '.': addToken(TK_DOT);
            break;
        case ',': addToken(TK_COMMA);
            break;
        case ';': addToken(TK_SEMICOLON);
            break;
        case ':': addToken(match('=') ? TK_DOUBLE_COLON : TK_COLON);

        case '\n':
        case ' ': break;

        case '\'': _char();break;
        case '\"': _string();break;
    }

    if (isdigit(c)) _number();
    else if (isalpha(c)) _identifier();
}

char Lexer::advance() {
    column++;
    return source[current++];
}

bool Lexer::isAtEnd() {
    return current >= source.length();
}

void Lexer::addToken(TokenType type) {
    addToken(type, "");
}

void Lexer::addToken(TokenType type, std::string literal) {
    std::string text = source.substr(start, current - start);
    tokens.emplace_back(text, literal, type, line, column);
}

bool Lexer::match(char expected) {
    if (isAtEnd()) return false;
    if (source[current] != expected) return false;

    current++;
    column++;

    return true;
}


char Lexer::peekNext() {
    if (isAtEnd()) return '\0';
    return source[current];
}

void Lexer::_number() {
    while (isdigit(peekNext())) advance();
    auto str = source.substr(start, current - start);
    addToken(TK_NUMBER, str);
}

void Lexer::_char() {
    TODO("No char implemented");
}

void Lexer::_string() {
    TODO("No string implemented");
}

void Lexer::_identifier() {
    while (isalnum(peekNext())) advance();
    auto str = source.substr(start, current - start);
    if (keywords.find(str) != keywords.end()) {
        addToken(keywords[str]);
        return;
    }
    addToken(TK_IDENTIFIER, source.substr(start, current - start));
}

void Lexer::_comment() {
    while (peekNext() != '\n' && !isAtEnd()) advance();
}
