//
// Created by nikolas on 5/10/26.
//

#include "Parser.h"
#include "../stupid.h"
#include "../Ares/Ares.h"

struct ParseError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

Parser::Parser(std::vector<Token> tokens) : tokens(std::move(tokens)) {
    if (this->tokens.empty()) {
        this->tokens.emplace_back("", "", TK_EOF, 0, 0);
    }
}

std::unique_ptr<Program> Parser::parseProgram() {
    std::vector<std::unique_ptr<Node>> declarations;
    while (!isAtEnd()) {
        declarations.push_back(parseDeclaration());
    }
    return std::make_unique<Program>(std::move(declarations));
}

std::unique_ptr<Node> Parser::parseDeclaration() {
    try {
        if (match({TK_INT, TK_FLOAT, TK_CHAR, TK_BOOL, TK_STRING, TK_VOID, TK_MAIN})) {
            Token type = previous();
            Token name;
            if (match({TK_IDENTIFIER})) {
                name = previous();
            } else if (match({TK_MAIN})) {
                name = previous();
            } else {
                throw ParseError("Expect identifier after type.");
            }

            if (match({TK_LEFT_PAREN})) {
                // Function declaration
                std::vector<std::pair<Token, Token>> parameters;
                if (!check(TK_RIGHT_PAREN)) {
                    do {
                        if (!match({TK_INT, TK_FLOAT, TK_CHAR, TK_BOOL, TK_STRING})) {
                             throw ParseError("Expect parameter type.");
                        }
                        Token pType = previous();
                        Token pName = consume(TK_IDENTIFIER, "Expect parameter name.");
                        parameters.emplace_back(pType, pName);
                    } while (match({TK_COMMA}));
                }
                consume(TK_RIGHT_PAREN, "Expect ')' after parameters.");
                consume(TK_LEFT_BRACE, "Expect '{' before function body.");
                auto blockNode = parseBlock();
                auto* blockStmt = dynamic_cast<BlockStmt*>(blockNode.get());
                if (!blockStmt) {
                     throw ParseError("Expect block body for function.");
                }
                blockNode.release();
                auto body = std::unique_ptr<BlockStmt>(blockStmt);
                return std::make_unique<FunctionDecl>(type, name, std::move(parameters), std::move(body));
            } else {
                // Variable declaration
                std::unique_ptr<Expr> initializer = nullptr;
                if (match({TK_ASSIGN})) {
                    initializer = parseExpression();
                }
                match({TK_SEMICOLON});
                return std::make_unique<VarDeclStmt>(type, name, std::move(initializer));
            }
        }
        return parseStatement();
    } catch (const std::exception& e) {
        synchronize();
        return nullptr;
    }
}

std::unique_ptr<Stmt> Parser::parseStatement() {
    if (match({TK_STDOUT})) {
        consume(TK_LEFT_SHIFT, "Expect '<<' after 'stdout'.");
        std::vector<std::unique_ptr<Expr>> expressions;
        do {
            expressions.push_back(parseExpression());
        } while (match({TK_LEFT_SHIFT}));
        match({TK_SEMICOLON});
        return std::make_unique<PrintStmt>(std::move(expressions));
    }

    if (match({TK_STDIN})) {
        consume(TK_RIGHT_SHIFT, "Expect '>>' after 'stdin'.");
        std::vector<std::unique_ptr<Expr>> targets;
        do {
            targets.push_back(parseExpression());
        } while (match({TK_RIGHT_SHIFT}));
        match({TK_SEMICOLON});
        return std::make_unique<ReadStmt>(std::move(targets));
    }

    if (match({TK_RETURN})) {
        std::unique_ptr<Expr> value = nullptr;
        if (!check(TK_SEMICOLON)) {
            value = parseExpression();
        }
        match({TK_SEMICOLON});
        return std::make_unique<ReturnStmt>(std::move(value));
    }

    if (match({TK_LEFT_BRACE})) return parseBlock();

    auto expr = parseExpression();
    match({TK_SEMICOLON});
    return std::make_unique<ExpressionStmt>(std::move(expr));
}

std::unique_ptr<Stmt> Parser::parseBlock() {
    std::vector<std::unique_ptr<Node>> statements;
    while (!check(TK_RIGHT_BRACE) && !isAtEnd()) {
        statements.push_back(parseDeclaration());
    }

    consume(TK_RIGHT_BRACE, "Expect '}' after block.");
    return std::make_unique<BlockStmt>(std::move(statements));
}

std::unique_ptr<Expr> Parser::parseExpression() {
    return parseAssignment();
}

std::unique_ptr<Expr> Parser::parseAssignment() {
    auto expr = parseEquality();

    if (match({TK_ASSIGN})) {
        Token equals = previous();
        auto value = parseAssignment();

        if (auto* varExpr = dynamic_cast<VariableExpr*>(expr.get())) {
            Token name = varExpr->name;
            return std::make_unique<AssignExpr>(name, std::move(value));
        }

        Ares::error(SYNTAX_ERROR, "Invalid assignment target.", previous().getErrorToken());
    }

    return expr;
}

std::unique_ptr<Expr> Parser::parseEquality() {
    auto expr = parseComparison();

    while (match({TK_EQUAL, TK_NOT_EQUAL})) {
        Token op = previous();
        auto right = parseComparison();
        expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::unique_ptr<Expr> Parser::parseComparison() {
    auto expr = parseTerm();

    while (match({TK_GREATER, TK_GREATER_EQUAL, TK_LESS, TK_LESS_EQUAL})) {
        Token op = previous();
        auto right = parseTerm();
        expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::unique_ptr<Expr> Parser::parseTerm() {
    auto expr = parseFactor();

    while (match({TK_PLUS, TK_MINUS})) {
        Token op = previous();
        auto right = parseFactor();
        expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::unique_ptr<Expr> Parser::parseFactor() {
    auto expr = parseUnary();

    while (match({TK_STAR, TK_SLASH, TK_PERCENT})) {
        Token op = previous();
        auto right = parseUnary();
        expr = std::make_unique<BinaryExpr>(std::move(expr), op, std::move(right));
    }

    return expr;
}

std::unique_ptr<Expr> Parser::parseUnary() {
    if (match({TK_NOT, TK_MINUS})) {
        Token op = previous();
        auto right = parseUnary();
        return std::make_unique<UnaryExpr>(op, std::move(right));
    }

    return parsePrimary();
}

std::unique_ptr<Expr> Parser::parsePrimary() {
    if (match({TK_FALSE})) return std::make_unique<LiteralExpr>(previous());
    if (match({TK_TRUE})) return std::make_unique<LiteralExpr>(previous());
    if (match({TK_NULL})) return std::make_unique<LiteralExpr>(previous());

    if (match({TK_NUMBER, TK_STRING, TK_CHAR_LITERAL, TK_LITERAL})) {
        return std::make_unique<LiteralExpr>(previous());
    }

    if (match({TK_IDENTIFIER})) {
        Token name = previous();
        if (match({TK_LEFT_PAREN})) {
            std::vector<std::unique_ptr<Expr>> arguments;
            if (!check(TK_RIGHT_PAREN)) {
                do {
                    arguments.push_back(parseExpression());
                } while (match({TK_COMMA}));
            }
            consume(TK_RIGHT_PAREN, "Expect ')' after arguments.");
            auto callee = std::make_unique<VariableExpr>(name);
            return std::make_unique<CallExpr>(std::move(callee), std::move(arguments));
        }
        return std::make_unique<VariableExpr>(name);
    }

    if (match({TK_LEFT_PAREN})) {
        auto expr = parseExpression();
        consume(TK_RIGHT_PAREN, "Expect ')' after expression.");
        return expr;
    }
    Ares::error(SYNTAX_ERROR, "Expect expression.", previous().getErrorToken());
    return nullptr;
}

Token Parser::consume(TokenType type, const std::string& message) {
    if (peek().getType() == type) {
        return advance();
    }
    Ares::error(SYNTAX_ERROR, message, peek().getErrorToken());
    throw ParseError(message);
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
    return current >= tokens.size() || tokens[current].getType() == TK_EOF;
}

Token Parser::peek() const {
    if (isAtEnd()) return tokens.back();
    return tokens[current];
}

Token Parser::previous() const {
    if (current == 0) return tokens[0];
    return tokens[current - 1];
}

void Parser::synchronize() {
    advance();

    while (!isAtEnd()) {
        if (previous().getType() == TK_SEMICOLON) return;

        switch (peek().getType()) {
            case TK_INT:
            case TK_FLOAT:
            case TK_CHAR:
            case TK_BOOL:
            case TK_STRING:
            case TK_VOID:
            case TK_IF:
            case TK_WHILE:
            case TK_FOR:
            case TK_RETURN:
            case TK_STDOUT:
            case TK_STDIN:
                return;
            default:
                break;
        }

        advance();
    }
}
