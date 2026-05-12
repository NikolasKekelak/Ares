//
// Created by nikolas on 5/12/26.
//

#include "CodeGen.h"
#include "../AST/Node.h"

void CodeGen::generateCode(std::string asmName, std::unique_ptr<Node> program) {
    program->codegen(*this);
    std::ofstream file(asmName);
    for (auto &instruction: instructions) {
        file << instruction << std::endl;
    }
    file.close();
}

void CodeGen::addInstruction(const std::string &instruction) {
    instructions.push_back(instruction);
}

void CodeGen::addInstruction(std::vector<std::string> &instructions) {
    this->instructions.insert(
        this->instructions.end(),
        instructions.begin(),
        instructions.end()
        );
}

int CodeGen::getOffset(std::string variable) {
    if (!offsets.contains(variable)) {
        offsets[variable] = offset;
        offset += 8;
    }
    return offsets[variable];
}