//
// Created by nikolas on 5/10/26.
//

#include "Node.h"
#include "../CodeGen/CodeGen.h"
#include "../stupid.h"
#include <utility>

#define INDENT(indent) for (int i = 0; i < ((indent)*3); i++) std::cout << " ";

void BinaryExpr::print(int indent) {
    INDENT(indent)
    op.print();
    std::cout << std::endl;
    left->print(indent + 1);
    std::cout << std::endl;
    right->print(indent + 1);
}

BinaryExpr::BinaryExpr(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right)
    : left(std::move(left)), op(std::move(op)), right(std::move(right)) {
}


void BinaryExpr::codegen(CodeGen &ctx) {
    left->codegen(ctx);
    ctx.addInstruction("    pop rax");
    right->codegen(ctx);
    ctx.addInstruction("    pop rbx");

    switch (op.getType()) {
        case TK_PLUS:
            ctx.addInstruction({
                "    add rax, rbx"
            });
            break;
        case TK_MINUS:
            ctx.addInstruction({
                "    mov rcx, rax"
                "    mov rax, rbx"
                "    sub rax, rcx"
            });
            break;
        case TK_STAR:
            ctx.addInstruction({
                "    imul rax, rbx"
            });
        case TK_SLASH:
            ctx.addInstruction({
                "    mov rcx, rax"
                "    mov rax, rbx"
                "    cqo"
                "    idiv rcx"
            });
        default: TODO("Unknown binary operator");
    }

}

void UnaryExpr::print(int indent) {
    INDENT(indent)
    op.print();
    std::cout << std::endl;
    right->print(indent + 1);
}

UnaryExpr::UnaryExpr(Token op, std::unique_ptr<Expr> right)
    : op(std::move(op)), right(std::move(right)) {
}

void UnaryExpr::codegen(CodeGen &ctx) {
}

LiteralExpr::LiteralExpr(Token value)
    : value(std::move(value)) {
}

void LiteralExpr::print(int indent) {
    INDENT(indent)
    value.print();
}

void LiteralExpr::codegen(CodeGen &ctx) {
    ctx.addInstruction("    mov rax, " + value.getLexeme());
}

VariableExpr::VariableExpr(Token name)
    : name(std::move(name)) {
}

void VariableExpr::print(int indent) {
    INDENT(indent)
    name.print();
}

void VariableExpr::codegen(CodeGen& ctx) {
    int offset = ctx.getOffset(name.getLexeme());
    ctx.addInstruction("mov rax, [rbp-" + std::to_string(offset) + "]");
}

AssignExpr::AssignExpr(Token name, std::unique_ptr<Expr> value)
    : name(std::move(name)), value(std::move(value)) {
}

void AssignExpr::print(int indent) {
    INDENT(indent)
    name.print();
    std::cout << std::endl;
    value->print(indent+1);
}

void AssignExpr::codegen(CodeGen &ctx) {
}

CallExpr::CallExpr(std::unique_ptr<Expr> callee, std::vector<std::unique_ptr<Expr> > arguments)
    : callee(std::move(callee)), arguments(std::move(arguments)) {
}

void CallExpr::print(int indent) {
    INDENT(indent)
    callee->print(0);
    std::cout << "(" << std::endl;
    for (auto &arg: arguments) {
        arg->print(indent + 1);
        std::cout << std::endl;
    }
    INDENT(indent)
    std::cout << ")";
}

void CallExpr::codegen(CodeGen &ctx) {
}

MemberAccessExpr::MemberAccessExpr(std::unique_ptr<Expr> object, Token member)
    : object(std::move(object)), member(std::move(member)) {
}

void MemberAccessExpr::print(int indent) {
    INDENT(indent)
    object->print(0);
    std::cout << ".";
    member.print();
    std::cout << std::endl;
}

void MemberAccessExpr::codegen(CodeGen &ctx) {
}

BlockStmt::BlockStmt(std::vector<std::unique_ptr<Node> > statements)
    : statements(std::move(statements)) {
}

void BlockStmt::print(int indent) {
    INDENT(indent)
    std::cout << "{" << std::endl;
    for (auto &stmt: statements) {
        stmt->print(indent + 1);
    }
    INDENT(indent)
    std::cout << "}" << std::endl;
}

void BlockStmt::codegen(CodeGen& ctx) {
    for (auto& stmt : statements) {
        stmt->codegen(ctx);
    }
}

VarDeclStmt::VarDeclStmt(Token type, Token name, std::unique_ptr<Expr> initializer)
    : type(std::move(type)), name(std::move(name)), initializer(std::move(initializer)) {
}

void VarDeclStmt::print(int indent) {
    INDENT(indent)
    type.print();
    std::cout << " ";
    name.print();
    if (initializer) {
        std::cout << "\n";
        INDENT(indent+1)
        std::cout << "= \n";
        initializer->print(indent+2);
    }
    std::cout << std::endl;
}

void VarDeclStmt::codegen(CodeGen &ctx) {
}

PrintStmt::PrintStmt(std::vector<std::unique_ptr<Expr> > expressions)
    : expressions(std::move(expressions)) {
}

void PrintStmt::print(int indent) {
    INDENT(indent)
    std::cout << "print " << std::endl;
    for (auto &expr: expressions) {
        expr->print(indent + 1);
    }
    std::cout << std::endl;
}

void PrintStmt::codegen(CodeGen &ctx) {
}

ReadStmt::ReadStmt(std::vector<std::unique_ptr<Expr> > targets)
    : targets(std::move(targets)) {
}

void ReadStmt::print(int indent) {
    INDENT(indent)
    std::cout << "read " << std::endl;
    for (auto &target: targets) {
        target->print(indent + 1);
    }
    std::cout << std::endl;
}

void ReadStmt::codegen(CodeGen &ctx) {
}

ExpressionStmt::ExpressionStmt(std::unique_ptr<Expr> expression)
    : expression(std::move(expression)) {
}

void ExpressionStmt::print(int indent) {
    expression->print(indent);
    std::cout << std::endl;
}

void ExpressionStmt::codegen(CodeGen &ctx) {
}

ReturnStmt::ReturnStmt(std::unique_ptr<Expr> value)
    : value(std::move(value)) {
}

void ReturnStmt::print(int indent) {
    INDENT(indent)
    std::cout << "return";
    if (value) {
        std::cout << std::endl;
        value->print(indent+1);
    }
    std::cout << std::endl;
}

void ReturnStmt::codegen(CodeGen &ctx) {
}

FunctionDecl::FunctionDecl(Token returnType, Token name, std::vector<std::pair<Token, Token> > parameters,
                           std::unique_ptr<BlockStmt> body)
    : returnType(std::move(returnType)), name(std::move(name)), parameters(std::move(parameters)),
      body(std::move(body)) {
}

void FunctionDecl::print(int indent) {
    INDENT(indent)
    returnType.print();
    std::cout << " ";
    name.print();
    std::cout << "(";
    for (int i = 0; i < parameters.size(); i++) {
        if (i != 0) std::cout << ", ";
        parameters[i].first.print();
        std::cout << " ";
        parameters[i].second.print();
    }
    std::cout << ")" << std::endl;
    body->print(indent + 1);
}

void FunctionDecl::codegen(CodeGen& ctx) {
    ctx.addInstruction("");
    ctx.addInstruction("main:");
    ctx.addInstruction("    push rbp");
    ctx.addInstruction("    mov rbp, rsp");

    int stackSize = 256;
    ctx.addInstruction("    sub rsp, " + std::to_string(stackSize));

    body->codegen(ctx);

    ctx.addInstruction("    xor rax, rax");
    ctx.addInstruction("    mov rsp, rbp");
    ctx.addInstruction("    pop rbp");
    ctx.addInstruction("    ret");
}

Program::Program(std::vector<std::unique_ptr<Node> > declarations)
    : declarations(std::move(declarations)) {
}

void Program::print(int indent) {
    INDENT(indent)
    std::cout << "Program: " << std::endl;
    for (auto &decl: declarations) {
        decl->print(indent + 1);
    }
    std::cout << std::endl;
}

void Program::codegen(CodeGen& ctx) {
    ctx.addInstruction("global main");
    ctx.addInstruction("extern printf");
    ctx.addInstruction("");

    ctx.addInstruction("section .data");
    ctx.addInstruction("    fmt_int db \"%d\", 10, 0");
    ctx.addInstruction("");

    ctx.addInstruction("section .text");

    for (auto& decl : declarations) {
        decl->codegen(ctx);
    }
}