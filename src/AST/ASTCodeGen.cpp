//
// Created by nikolas on 5/12/26.
//

#include "Node.h"
#include "../CodeGen/CodeGen.h"
#include "../stupid.h"
#include <utility>


void BinaryExpr::codegen(CodeGen &ctx) {
    left->codegen(ctx);
    ctx.pushRax();
    right->codegen(ctx);
    ctx.popTo("r10");

    switch (op.getType()) {
        case TK_PLUS:
            ctx.addInstruction("    add rax, r10");
            break;
        case TK_MINUS:
            ctx.addInstruction("    mov r11, rax");
            ctx.addInstruction("    mov rax, r10");
            ctx.addInstruction("    sub rax, r11");
            break;
        case TK_STAR:
            ctx.addInstruction("    imul rax, r10");
            break;
        case TK_SLASH:
            ctx.addInstruction("    mov r11, rax");
            ctx.addInstruction("    mov rax, r10");
            ctx.addInstruction("    cqo");
            ctx.addInstruction("    idiv r11");
            break;
        default: TODO("Unknown binary operator");
    }
    ctx.addInstruction("");

}
void UnaryExpr::codegen(CodeGen &ctx) {
}
void LiteralExpr::codegen(CodeGen &ctx) {
    ctx.addInstruction("    mov rax, " + value.getLexeme());
    ctx.addInstruction("");
}
void VariableExpr::codegen(CodeGen& ctx) {
    int offset = ctx.getOffset(name.getLexeme());
    ctx.addInstruction("    mov rax, [rbp-" + std::to_string(offset) + "]");
    ctx.addInstruction("");
}
void AssignExpr::codegen(CodeGen &ctx) {
    ctx.addInstruction("");
}
void CallExpr::codegen(CodeGen& ctx) {

    static const char* ARG_REGS[] = {
        "rdi",
        "rsi",
        "rdx",
        "rcx",
        "r8",
        "r9"
    };

    constexpr int REGISTER_ARG_COUNT = sizeof(ARG_REGS) / sizeof(ARG_REGS[0]);

    if (arguments.size() > REGISTER_ARG_COUNT) {
        TODO("more than six call arguments are not supported yet");
    }

    for (int i = static_cast<int>(arguments.size()) - 1; i >= 0; i--) {

        arguments[i]->codegen(ctx);
        ctx.pushRax();
    }

    for (int i = 0; i < arguments.size(); i++) {
        ctx.popTo(ARG_REGS[i]);
    }

    auto* var = dynamic_cast<VariableExpr*>(callee.get());

    if (!var) {
        TODO("only direct function calls supported");
    }

    bool aligned = ctx.alignStackForCall();
    ctx.addInstruction("    call " + var->name.getLexeme());
    ctx.restoreStackAfterCall(aligned);
}
void MemberAccessExpr::codegen(CodeGen &ctx) {
    TODO("Member access node print")
    ctx.addInstruction("");
}
void BlockStmt::codegen(CodeGen& ctx) {
    for (auto& stmt : statements) {
        stmt->codegen(ctx);
    }
    ctx.addInstruction("");
}
void VarDeclStmt::codegen(CodeGen& ctx) {
    auto offset = ctx.getOffset(name.getLexeme());
    initializer->codegen(ctx);
    ctx.addInstruction(
        "    mov [rbp-" +
        std::to_string(offset) +
        "], rax"
    );
    ctx.addInstruction("");
}
void PrintStmt::codegen(CodeGen& ctx) {

    expressions[0]->codegen(ctx);

    ctx.addInstruction("    mov rsi, rax");
    ctx.addInstruction("    lea rdi, [rel fmt_int]");
    ctx.addInstruction("    xor rax, rax");
    bool aligned = ctx.alignStackForCall();
    ctx.addInstruction("    call printf");
    ctx.restoreStackAfterCall(aligned);
    ctx.addInstruction("");
}
void ReadStmt::codegen(CodeGen &ctx) {
    TODO("Read statement codegen")
    ctx.addInstruction("");
}
void ExpressionStmt::codegen(CodeGen &ctx) {
    if (expression) {
        expression->codegen(ctx);
    }
    ctx.addInstruction("");
}
void ReturnStmt::codegen(CodeGen& ctx) {

    if (value) {
        value->codegen(ctx);
    } else {
        ctx.addInstruction("    xor rax, rax");
    }

    ctx.addInstruction("    mov rsp, rbp");
    ctx.addInstruction("    pop rbp");
    ctx.addInstruction("    ret");
}
void FunctionDecl::codegen(CodeGen& ctx) {
    static const char* ARG_REGS[] = {
        "rdi",
        "rsi",
        "rdx",
        "rcx",
        "r8",
        "r9"
    };

    constexpr int REGISTER_ARG_COUNT = sizeof(ARG_REGS) / sizeof(ARG_REGS[0]);

    if (parameters.size() > REGISTER_ARG_COUNT) {
        TODO("more than six function parameters are not supported yet");
    }

    ctx.beginFunction();
    ctx.addInstruction("");
    ctx.addInstruction(name.getLexeme()+":");
    ctx.addInstruction("    push rbp");
    ctx.addInstruction("    mov rbp, rsp");

    int stackSize = 256;
    ctx.addInstruction("    sub rsp, " + std::to_string(stackSize));

    for (int i = 0; i < parameters.size(); i++) {
        int parameterOffset = ctx.declareVariable(parameters[i].second.getLexeme());
        ctx.addInstruction(
            "    mov [rbp-" +
            std::to_string(parameterOffset) +
            "], " +
            ARG_REGS[i]
        );
    }

    body->codegen(ctx);

    ctx.addInstruction("    xor rax, rax");
    ctx.addInstruction("    mov rsp, rbp");
    ctx.addInstruction("    pop rbp");
    ctx.addInstruction("    ret");
    ctx.addInstruction("");
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
    ctx.addInstruction("");
}