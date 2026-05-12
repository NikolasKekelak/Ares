//
// Created by nikolas on 5/10/26.
//

#ifndef ARES_NODE_H
#define ARES_NODE_H

#include <string>
#include <vector>
#include <memory>

#include "../Tokens/Token.h"

class CodeGen;
class Node {
public:
    virtual ~Node() = default;
    virtual void codegen(CodeGen& ctx) = 0;
    virtual void print(int indent) = 0;
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
    Token op; // TK_STAR,TK_PLUS,MINUS
    std::unique_ptr<Expr> right;

    void print(int indent) override;
    BinaryExpr(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right);
    void codegen(CodeGen& ctx) override;
};

class UnaryExpr : public Expr {
public:
    Token op;
    std::unique_ptr<Expr> right;

    void print(int indent) override;
    UnaryExpr(Token op, std::unique_ptr<Expr> right);
    void codegen(CodeGen& ctx) override;
};

class LiteralExpr : public Expr {
public:
    Token value;

    explicit LiteralExpr(Token value);
    void print(int indent) override;
    void codegen(CodeGen& ctx) override;
};

class VariableExpr : public Expr {
public:
    Token name;

    explicit VariableExpr(Token name);
    void print(int indent) override;
    void codegen(CodeGen& ctx) override;

};

class AssignExpr : public Expr {
public:
    Token name;
    std::unique_ptr<Expr> value;

    AssignExpr(Token name, std::unique_ptr<Expr> value);
    void print(int indent) override;
    void codegen(CodeGen& ctx) override;
};

class CallExpr : public Expr {
public:
    std::unique_ptr<Expr> callee;
    std::vector<std::unique_ptr<Expr>> arguments;

    CallExpr(std::unique_ptr<Expr> callee, std::vector<std::unique_ptr<Expr>> arguments);
    void print(int indent) override;
    void codegen(CodeGen& ctx) override;


};

class MemberAccessExpr : public Expr {
public:
    std::unique_ptr<Expr> object;
    Token member;

    MemberAccessExpr(std::unique_ptr<Expr> object, Token member);
    void print(int indent) override;
    void codegen(CodeGen& ctx) override;

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
    void print(int indent) override;
    void codegen(CodeGen& ctx) override;
};

class VarDeclStmt : public Stmt {
public:
    Token type;
    Token name;
    std::unique_ptr<Expr> initializer;

    VarDeclStmt(Token type, Token name, std::unique_ptr<Expr> initializer);
    void print(int indent) override;
    void codegen(CodeGen& ctx) override;
};

class PrintStmt : public Stmt {
public:
    std::vector<std::unique_ptr<Expr>> expressions;

    explicit PrintStmt(std::vector<std::unique_ptr<Expr>> expressions);
    void print(int indent) override;
    void codegen(CodeGen& ctx) override;
};

class ReadStmt : public Stmt {
public:
    std::vector<std::unique_ptr<Expr>> targets;

    explicit ReadStmt(std::vector<std::unique_ptr<Expr>> targets);
    void print(int indent) override;
    void codegen(CodeGen& ctx) override;
};

class ExpressionStmt : public Stmt {
public:
    std::unique_ptr<Expr> expression;

    explicit ExpressionStmt(std::unique_ptr<Expr> expression);
    void print(int indent) override;
    void codegen(CodeGen& ctx) override;
};

class ReturnStmt : public Stmt {
public:
    std::unique_ptr<Expr> value;

    explicit ReturnStmt(std::unique_ptr<Expr> value);
    void print(int indent) override;
    void codegen(CodeGen& ctx) override;
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
    void print(int indent) override;
    void codegen(CodeGen& ctx) override;
};

class Program : public Node {
public:
    std::vector<std::unique_ptr<Node>> declarations;

    explicit Program(std::vector<std::unique_ptr<Node>> declarations);
    void print(int indent) override;
    void codegen(CodeGen& ctx) override;
};

#endif // ARES_NODE_H
