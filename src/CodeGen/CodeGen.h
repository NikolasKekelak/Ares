//
// Created by nikolas on 5/12/26.
//

#ifndef ARES_CODEGEN_H
#define ARES_CODEGEN_H

#include <map>
#include <memory>
#include <string>
#include <vector>

class Node;

class CodeGen {
    std::vector<std::string> instructions = {};
    std::map<std::string, int> offsets = {};
    int offset = 8;
    int temporaryStackSlots = 0;
    int labelCounter = 0;

public:

    void generateCode(
        std::string asmName,
        std::unique_ptr<Node> program
        );

    void addInstruction(const std::string &instruction);
    void addInstruction(std::vector<std::string> &instructions);

    void beginFunction();
    void pushRax();
    void popTo(const std::string& registerName);
    bool alignStackForCall();

    void restoreStackAfterCall(bool wasAligned);
    int declareVariable(const std::string& variable, const std::string& type);
    int getOffset(std::string variable);

    std::string makeLabel(const std::string &base);
};



#endif //ARES_CODEGEN_H
