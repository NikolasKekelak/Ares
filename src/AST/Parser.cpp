//
// Created by nikolas on 5/10/26.
//

#include "Parser.h"
#include "../stupid.h"

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
    TODO("Consume a token of a specific type or report a syntax error");
}

bool Parser::match(const std::vector<TokenType>& types) {
    TODO("Check if the current token matches any of the given types and advance if it does");
}

bool Parser::check(TokenType type) const {
    return peek().getType() == type;
}

Token Parser::advance() {
    return tokens[current++];
}

bool Parser::isAtEnd() const {
    return current >= tokens.size();
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
