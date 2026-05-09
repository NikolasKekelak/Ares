//
// Created by nikolas on 5/9/26.
//

#ifndef ARES_TEST_COMPILE_TOKENS_TO_ASM_H
#define ARES_TEST_COMPILE_TOKENS_TO_ASM_H
#include <string>
#include <vector>
#include <fstream>
#include <map>

#include "../Tokens/Token.h"

class Token;

//
// global main
// extern printf
//
// section .data
//     format db "%d", 10, 0   ; "%d\n"
//
// section .text
//
// main:
//     ; int x = 5;
//     mov rax, 5
//     mov rbx, 5
//
//     ; int z = x + y;
//     add rax, rbx
//
//     ; printf("%d", z);
//     mov rsi, rax        ; second argument = z
//     lea rdi, [rel format] ; first argument = format string
//     xor rax, rax        ; required before printf
//     call printf
//
// ret

// This function was there only for testing, use only when you know what are you doing
void compile_tokens_to_asm(std::string filename,
    std::vector<std::string> externs,
    std::map<std::string, std::string> data,
    std::vector<Token> &tokens
    ){
    std::ofstream out(filename);
    // header
    
    
    int counter = 1;
    std::map<std::string, int> mapping;
    
    out << "global main\n"
           "\n";
    if (externs.size() > 0) {
        for (int i = 0; i < externs.size(); i++) {
            out << "extern " << externs[i]<<"\n";
        }
        out << "\n";
    }
    //Global data there
    if (!data.empty()) {
        out << "section .data\n";
        for (auto &[name, val] : data) {
            out << "    " << name << " db " << val << ",10 , 0\n";
        }
    }

    out << "section .text\n"
           "main:\n";
    out << "    push rbp\n"
           "    mov rbp, rsp\n";
    out << "    sub rsp, 256\n\n";
    // processing main here
    for (int i = 0; i < tokens.size(); i++) {
        switch (tokens[i].getType()) {
            case TK_STDOUT:
                out << "    mov rsi, [rbp-"  << mapping[tokens[i+2].getLexeme()]*8<<"]\n";
                out << "    lea rdi, [rel "  << tokens[i+1].getLexeme()<<"]\n";
                out << "    xor rax, rax\n";
                out << "    call printf\n";
                i=+2;
                break;
            case TK_INT:
                mapping[tokens[i].getLexeme()] = counter++;
                out << "    mov qword [rbp-"<<mapping[tokens[i].getLexeme()]*8<<"], "<< tokens[i+1].getLexeme() << "\n";
                i++;
                break;
        }
    }
    out << "    mov rsp, rbp\n";
    out << "    pop rbp\n";
    out << "\n\n    xor rax, rax\n";
    out << "    ret\n";
    out.close();
    // system("make");
}

#endif //ARES_TEST_COMPILE_TOKENS_TO_ASM_H
