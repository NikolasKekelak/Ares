//
// Created by nikolas on 5/10/26.
//

#include "Node.h"
#include "../stupid.h"
#include <utility>

BinaryExpr::BinaryExpr(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right)
    : left(std::move(left)), op(std::move(op)), right(std::move(right)) {
    TODO("Implement BinaryExpr initialization if needed");
}

UnaryExpr::UnaryExpr(Token op, std::unique_ptr<Expr> right)
    : op(std::move(op)), right(std::move(right)) {
    TODO("Implement UnaryExpr initialization if needed");
}

LiteralExpr::LiteralExpr(Token value)
    : value(std::move(value)) {
    TODO("Implement LiteralExpr initialization if needed");
}

VariableExpr::VariableExpr(Token name)
    : name(std::move(name)) {
    TODO("Implement VariableExpr initialization if needed");
}

AssignExpr::AssignExpr(Token name, std::unique_ptr<Expr> value)
    : name(std::move(name)), value(std::move(value)) {
    TODO("Implement AssignExpr initialization if needed");
}

CallExpr::CallExpr(std::unique_ptr<Expr> callee, std::vector<std::unique_ptr<Expr>> arguments)
    : callee(std::move(callee)), arguments(std::move(arguments)) {
    TODO("Implement CallExpr initialization if needed");
}

MemberAccessExpr::MemberAccessExpr(std::unique_ptr<Expr> object, Token member)
    : object(std::move(object)), member(std::move(member)) {
    TODO("Implement MemberAccessExpr initialization if needed");
}

BlockStmt::BlockStmt(std::vector<std::unique_ptr<Node>> statements)
    : statements(std::move(statements)) {
    TODO("Implement BlockStmt initialization if needed");
}

VarDeclStmt::VarDeclStmt(Token type, Token name, std::unique_ptr<Expr> initializer)
    : type(std::move(type)), name(std::move(name)), initializer(std::move(initializer)) {
    TODO("Implement VarDeclStmt initialization if needed");
}

PrintStmt::PrintStmt(std::vector<std::unique_ptr<Expr>> expressions)
    : expressions(std::move(expressions)) {
    TODO("Implement PrintStmt initialization if needed");
}

ReadStmt::ReadStmt(std::vector<std::unique_ptr<Expr>> targets)
    : targets(std::move(targets)) {
    TODO("Implement ReadStmt initialization if needed");
}

ExpressionStmt::ExpressionStmt(std::unique_ptr<Expr> expression)
    : expression(std::move(expression)) {
    TODO("Implement ExpressionStmt initialization if needed");
}

FunctionDecl::FunctionDecl(Token returnType, Token name, std::vector<std::pair<Token, Token>> parameters, std::unique_ptr<BlockStmt> body)
    : returnType(std::move(returnType)), name(std::move(name)), parameters(std::move(parameters)), body(std::move(body)) {
    TODO("Implement FunctionDecl initialization if needed");
}

Program::Program(std::vector<std::unique_ptr<Node>> declarations)
    : declarations(std::move(declarations)) {
    TODO("Implement Program initialization if needed");
}
