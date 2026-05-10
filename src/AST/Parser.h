//
// Created by nikolas on 5/10/26.
//

#ifndef ARES_PARSER_H
#define ARES_PARSER_H

#include <vector>
#include <memory>
#include "Node.h"
#include "../Tokens/Token.h"

class Parser {
public:
    explicit Parser(std::vector<Token> tokens);

    std::unique_ptr<Program> parseProgram();

private:
    std::unique_ptr<Node> parseDeclaration();
    std::unique_ptr<Stmt> parseStatement();
    std::unique_ptr<Stmt> parseBlock();
    std::unique_ptr<Expr> parseExpression();
    std::unique_ptr<Expr> parseAssignment();
    std::unique_ptr<Expr> parseEquality();
    std::unique_ptr<Expr> parseComparison();
    std::unique_ptr<Expr> parseTerm();
    std::unique_ptr<Expr> parseFactor();
    std::unique_ptr<Expr> parseUnary();
    std::unique_ptr<Expr> parsePrimary();

    Token consume(TokenType type, const std::string& message);
    bool match(const std::vector<TokenType>& types);
    bool check(TokenType type) const;
    Token advance();
    bool isAtEnd() const;
    Token peek() const;
    Token previous() const;

    void synchronize();

    std::vector<Token> tokens;
    int current = 0;
};

#endif // ARES_PARSER_H
