//
// Created by nikolas on 5/10/26.
//

#include "Node.h"

#include "../Datatypes/DTT.h"


#define INDENT(indent) for (int i = 0; i < ((indent)*3); i++) std::cout << " ";

int Node::getStackSize() {
    return 0;
}

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


void UnaryExpr::print(int indent) {
    INDENT(indent)
    op.print();
    std::cout << std::endl;
    right->print(indent + 1);
}


UnaryExpr::UnaryExpr(Token op, std::unique_ptr<Expr> right)
    : op(std::move(op)), right(std::move(right)) {
}


LiteralExpr::LiteralExpr(Token value)
    : value(std::move(value)) {
}

void LiteralExpr::print(int indent) {
    INDENT(indent)
    value.print();
}


VariableExpr::VariableExpr(Token name)
    : name(std::move(name)) {
}

void VariableExpr::print(int indent) {
    INDENT(indent)
    name.print();
}

AssignExpr::AssignExpr(Token name, std::unique_ptr<Expr> value)
    : name(std::move(name)), value(std::move(value)) {
}

void AssignExpr::print(int indent) {
    INDENT(indent)
    name.print();
    std::cout << std::endl;
    value->print(indent + 1);
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
        initializer->print(indent + 2);
    }
    std::cout << std::endl;
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


ExpressionStmt::ExpressionStmt(std::unique_ptr<Expr> expression)
    : expression(std::move(expression)) {
}

void ExpressionStmt::print(int indent) {
    expression->print(indent);
    std::cout << std::endl;
}


ReturnStmt::ReturnStmt(std::unique_ptr<Expr> value)
    : value(std::move(value)) {
}

void ReturnStmt::print(int indent) {
    INDENT(indent)
    std::cout << "return";
    if (value) {
        std::cout << std::endl;
        value->print(indent + 1);
    }
    std::cout << std::endl;
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
        case TK_EQUAL:
            ctx.addInstruction("    cmp r10, rax");
            ctx.addInstruction("    sete al");
            ctx.addInstruction("    movzx rax, al");
            break;

        case TK_NOT_EQUAL:
            ctx.addInstruction("    cmp r10, rax");
            ctx.addInstruction("    setne al");
            ctx.addInstruction("    movzx rax, al");
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

void VariableExpr::codegen(CodeGen &ctx) {
    int offset = ctx.getOffset(name.getLexeme());
    ctx.addInstruction("    mov rax, [rbp-" + std::to_string(offset) + "]");
    ctx.addInstruction("");
}

void AssignExpr::codegen(CodeGen &ctx) {
    ctx.addInstruction("");
}

void CallExpr::codegen(CodeGen &ctx) {
    static const char *ARG_REGS[] = {
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

    auto *var = dynamic_cast<VariableExpr *>(callee.get());

    if (!var) {
        TODO("only direct function calls supported");
    }

    bool aligned = ctx.alignStackForCall();
    ctx.addInstruction("    call " + var->name.getLexeme());
    ctx.restoreStackAfterCall(aligned);
}

void MemberAccessExpr::codegen(CodeGen &ctx) {
    TODO("Member access node print");
    ctx.addInstruction("");
}

void BlockStmt::codegen(CodeGen &ctx) {
    for (auto &stmt: statements) {
        stmt->codegen(ctx);
    }
    ctx.addInstruction("");
}

int BlockStmt::getStackSize() {
    int size = 0;
    for (auto &stmt: statements) {
        size+=stmt->getStackSize();
    }
    return size;
}

void VarDeclStmt::codegen(CodeGen &ctx) {
    auto offset = ctx.getOffset(name.getLexeme());
    initializer->codegen(ctx);
    ctx.addInstruction(
        "    mov [rbp-" +
        std::to_string(offset) +
        "], rax"
    );
    ctx.addInstruction("");
}

int VarDeclStmt::getStackSize() {
    return DTT::getSize(type.getLexeme());
}

void PrintStmt::codegen(CodeGen &ctx) {
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
    TODO("Read statement codegen");
    ctx.addInstruction("");
}

void ExpressionStmt::codegen(CodeGen &ctx) {
    if (expression) {
        expression->codegen(ctx);
    }
    ctx.addInstruction("");
}

void ReturnStmt::codegen(CodeGen &ctx) {
    if (value) {
        value->codegen(ctx);
    } else {
        ctx.addInstruction("    xor rax, rax");
    }

    ctx.addInstruction("    mov rsp, rbp");
    ctx.addInstruction("    pop rbp");
    ctx.addInstruction("    ret");
}

IfStmt::IfStmt(
    std::unique_ptr<Expr> condition,
    std::unique_ptr<Stmt> thenBranch,
    std::unique_ptr<Stmt> elseBranch
) : condition(std::move(condition)),
    thenBranch(std::move(thenBranch)),
    elseBranch(std::move(elseBranch)) {
}

void IfStmt::print(int indent) {
    INDENT(indent)
    std::cout << "if" << std::endl;

    condition->print(indent + 1);
    std::cout << std::endl;

    thenBranch->print(indent + 1);

    if (elseBranch) {
        INDENT(indent)
        std::cout << "else" << std::endl;
        elseBranch->print(indent + 1);
    }
}

void IfStmt::codegen(CodeGen &ctx) {
    std::string elseLabel = ctx.makeLabel("else");
    std::string endLabel  = ctx.makeLabel("endif");

    // condition result in rax
    condition->codegen(ctx);

    ctx.addInstruction("    cmp rax, 0");

    if (elseBranch) {
        ctx.addInstruction("    je " + elseLabel);
    } else {
        ctx.addInstruction("    je " + endLabel);
    }

    // THEN
    thenBranch->codegen(ctx);

    // skip else
    if (elseBranch) {
        ctx.addInstruction("    jmp " + endLabel);
    }

    // ELSE LABEL
    if (elseBranch) {
        ctx.addInstruction(elseLabel + ":");
        elseBranch->codegen(ctx);
    }

    // END LABEL
    ctx.addInstruction(endLabel + ":");
}

void FunctionDecl::codegen(CodeGen &ctx) {
    static const char *ARG_REGS[] = {
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
    ctx.addInstruction(name.getLexeme() + ":");
    ctx.addInstruction("    push rbp");
    ctx.addInstruction("    mov rbp, rsp");

    int stackSize = STACK_OFFSET + body->getStackSize();
    for (int i = 0; i < parameters.size(); i++) {
        stackSize += DTT::getSize(parameters[i].first.getLiteral());
    }
    ctx.addInstruction("    sub rsp, " + std::to_string(stackSize));

    for (int i = 0; i < parameters.size(); i++) {
        int parameterOffset = ctx.declareVariable(parameters[i].second.getLexeme(), parameters[i].first.getLexeme());
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

void Program::codegen(CodeGen &ctx) {
    ctx.addInstruction("global main");
    ctx.addInstruction("extern printf");
    ctx.addInstruction("");

    ctx.addInstruction("section .data");
    ctx.addInstruction("    fmt_int db \"%d\", 10, 0");
    ctx.addInstruction("");

    ctx.addInstruction("section .text");

    for (auto &decl: declarations) {
        decl->codegen(ctx);
    }
    ctx.addInstruction("");
}
