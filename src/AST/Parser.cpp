//
// Created by nikolas on 5/10/26.
//

#include "Parser.h"
#include "../stupid.h"
#include "../Ares/Ares.h"

Parser::Parser(std::vector<Token> tokens) : tokens(std::move(tokens)) {
    TODO("Initialize parser state");
}

std::unique_ptr<Program> Parser::parseProgram() {
    TODO("Parse a sequence of top-level declarations");
}

std::unique_ptr<Node> Parser::parseDeclaration() {
    TODO("Parse a single declaration (function, variable, etc.)");
}

std::unique_ptr<Stmt> Parser::parseStatement() {
    TODO("Parse a statement (print, read, block, etc.)");
}

std::unique_ptr<Stmt> Parser::parseBlock() {
    TODO("Parse a block of statements enclosed in braces");
}

std::unique_ptr<Expr> Parser::parseExpression() {
    TODO("Parse an expression with correct operator precedence");
}

std::unique_ptr<Expr> Parser::parseAssignment() {
    TODO("Parse an assignment expression");
}

std::unique_ptr<Expr> Parser::parseEquality() {
    TODO("Parse equality expressions (==, !=)");
}

std::unique_ptr<Expr> Parser::parseComparison() {
    TODO("Parse comparison expressions (<, <=, >, >=)");
}

std::unique_ptr<Expr> Parser::parseTerm() {
    TODO("Parse term expressions (+, -)");
}

std::unique_ptr<Expr> Parser::parseFactor() {
    TODO("Parse factor expressions (*, /, %)");
}

std::unique_ptr<Expr> Parser::parseUnary() {
    TODO("Parse unary expressions (-, !)");
}

std::unique_ptr<Expr> Parser::parsePrimary() {
    TODO("Parse primary expressions (literals, identifiers, groupings)");
}

Token Parser::consume(TokenType type, const std::string& message) {
    if (peek().getType() == type) {
        return advance();
    }
    Ares::error(SYNTAX_ERROR, message);
}

bool Parser::match(const std::vector<TokenType>& types) {
    for (auto type : types) {
        if (check(type)) {
            advance();
            return true;
        }
    }
    return false;
}

bool Parser::check(TokenType type) const {
    if (isAtEnd()) return type == TK_EOF;
    return peek().getType() == type;
}

Token Parser::advance() {
    if (!isAtEnd()) current++;
    return previous();
}

bool Parser::isAtEnd() const {
    return tokens.empty() || peek().getType() == TK_EOF;
}
Token Parser::peek() const {
    return tokens[current];
}

Token Parser::previous() const {
    return tokens[current - 1];
}

void Parser::synchronize() {
    TODO("Recover from a syntax error by skipping tokens until a synchronization point");
}
