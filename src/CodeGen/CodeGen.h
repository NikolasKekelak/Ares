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
public:

    // This method
    void generateCode(
        std::string asmName,
        std::unique_ptr<Node> program
        );
    void addInstruction(const std::string &instruction);
    void addInstruction(std::vector<std::string> &instructions);
    int getOffset(std::string variable);

};



#endif //ARES_CODEGEN_H
