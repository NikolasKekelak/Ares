#include <iostream>

#include "src/Lexer/Lexer.h"
#include "src/temp_testing/test_compile_tokens_to_asm.h"

#include <string>
#include <fstream>
#include <sstream>

inline std::string readFileToString(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

int main() {

    auto source = readFileToString("test.ares");
    Lexer lexer;
    lexer.setSource(source);
    lexer.scanTokens();
    for (auto it: lexer.getTokens()) {
        it.print();
    }
    // std::vector<Token> program;
    // program.emplace_back("1", "x", TK_INT, 0, 0);
    // program.emplace_back("1", "1", TK_INT, 0, 0);
    // program.emplace_back("1", "printf", TK_STDOUT, 0, 0);
    // program.emplace_back("1", "format", TK_STRING, 0, 0);
    // program.emplace_back("1", "x",      TK_NUMBER , 0, 0);
    //
    // compile_tokens_to_asm(
    //     "test.asm"
    //     ,{"printf"},{
    //         {"format", "\"x = %d\""}
    //     },program
    //     );
     return 0;
}
