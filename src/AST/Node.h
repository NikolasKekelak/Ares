//
// Created by nikolas on 5/10/26.
//

#ifndef ARES_NODE_H
#define ARES_NODE_H

#include <string>
#include <vector>
#include <memory>
#include "../Tokens/Token.h"

/*
 * Base class for all AST nodes.
 * Future semantic analysis hooks and IR/codegen integration can be added here.
 */
class Node {
public:
    virtual ~Node() = default;
};

// --- Expressions ---

/*
 * Base class for all expression nodes.
 * Future type checking and symbol table information will be integrated here.
 */
class Expr : public Node {
public:
    virtual ~Expr() = default;
};

class BinaryExpr : public Expr {
public:
    std::unique_ptr<Expr> left;
    Token op;
    std::unique_ptr<Expr> right;

    BinaryExpr(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right);
};

class UnaryExpr : public Expr {
public:
    Token op;
    std::unique_ptr<Expr> right;

    UnaryExpr(Token op, std::unique_ptr<Expr> right);
};

class LiteralExpr : public Expr {
public:
    Token value;

    explicit LiteralExpr(Token value);
};

class VariableExpr : public Expr {
public:
    Token name;

    explicit VariableExpr(Token name);
};

class AssignExpr : public Expr {
public:
    Token name;
    std::unique_ptr<Expr> value;

    AssignExpr(Token name, std::unique_ptr<Expr> value);
};

class CallExpr : public Expr {
public:
    std::unique_ptr<Expr> callee;
    std::vector<std::unique_ptr<Expr>> arguments;

    CallExpr(std::unique_ptr<Expr> callee, std::vector<std::unique_ptr<Expr>> arguments);
};

class MemberAccessExpr : public Expr {
public:
    std::unique_ptr<Expr> object;
    Token member;

    MemberAccessExpr(std::unique_ptr<Expr> object, Token member);
};

// --- Statements ---

/*
 * Base class for all statement nodes.
 * Scope handling and control flow analysis can be hooked into these.
 */
class Stmt : public Node {
public:
    virtual ~Stmt() = default;
};

class BlockStmt : public Stmt {
public:
    std::vector<std::unique_ptr<Node>> statements;

    explicit BlockStmt(std::vector<std::unique_ptr<Node>> statements);
};

class VarDeclStmt : public Stmt {
public:
    Token type;
    Token name;
    std::unique_ptr<Expr> initializer;

    VarDeclStmt(Token type, Token name, std::unique_ptr<Expr> initializer);
};

class PrintStmt : public Stmt {
public:
    std::vector<std::unique_ptr<Expr>> expressions;

    explicit PrintStmt(std::vector<std::unique_ptr<Expr>> expressions);
};

class ReadStmt : public Stmt {
public:
    std::vector<std::unique_ptr<Expr>> targets;

    explicit ReadStmt(std::vector<std::unique_ptr<Expr>> targets);
};

class ExpressionStmt : public Stmt {
public:
    std::unique_ptr<Expr> expression;

    explicit ExpressionStmt(std::unique_ptr<Expr> expression);
};

// --- Declarations ---

/*
 * Base class for all declaration nodes.
 * Used for top-level constructs and symbol table population.
 */
class Decl : public Node {
public:
    virtual ~Decl() = default;
};

class FunctionDecl : public Decl {
public:
    Token returnType;
    Token name;
    std::vector<std::pair<Token, Token>> parameters;
    std::unique_ptr<BlockStmt> body;

    FunctionDecl(Token returnType, Token name, std::vector<std::pair<Token, Token>> parameters, std::unique_ptr<BlockStmt> body);
};

class Program : public Node {
public:
    std::vector<std::unique_ptr<Node>> declarations;

    explicit Program(std::vector<std::unique_ptr<Node>> declarations);
};

#endif // ARES_NODE_H
