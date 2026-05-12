//
// Created by nikolas on 5/12/26.
//

#ifndef ARES_CODEGEN_H
#define ARES_CODEGEN_H
#include <memory>
#include <string>

#include "../AST/Node.h"


class CodeGen {

public:

    // This method
    void generateCode(
        std::string asmName,
        std::unique_ptr<Node> program
        );
};



#endif //ARES_CODEGEN_H
