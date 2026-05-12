#include <cstring>
#include <iostream>

#include "src/Lexer/Lexer.h"
#include "src/temp_testing/test_compile_tokens_to_asm.h"

#include <string>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include "src/Ares/Ares.h"

inline std::string readFileToString(const std::string &filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

// humbly stolen from https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exists-using-standard-c-c11-14-17-c
inline bool file_exists (const std::string& name) {
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        Ares::help();
    }

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
            Ares::help();
            return 0;
        }
        if (!strcmp(argv[i], "-o") || !strcmp(argv[i], "--output")) {
            if (i + 1 >= argc)
                Ares::error(MISSING_ARGUMENT_AFTER_OUTPUT_FLAG);
            Ares::setOutputFile(argv[++i]);
            continue;
        }
        if (!strcmp(argv[i], "--emit-tokens")) {
            Ares::setPrintTokens();
            continue;
        }
        if (!strcmp(argv[i], "--emit-ast")) {
            Ares::setPrintAST();
            continue;
        }
        if (!strcmp(argv[i], "--emit-asm")) {
            Ares::setPrintASM();
            continue;
        }
        if (!strcmp(argv[i], "--emit-ir")) {
            Ares::setPrintIR();
            continue;
        }
        if (!strcmp(argv[i], "--no-compile")) {
            Ares::setNoCompile();
            continue;
        }
        if (!strcmp(argv[i], "--no-optim")) {
            if (Ares::getOptimizationLevel() != 0) {
                TODO("can change optimization only once")
            }
            Ares::setOptimizationLevel(-1);
            continue;
        }
        if (!strcmp(argv[i], "-O1")) {
            if (Ares::getOptimizationLevel() != 0) {
                TODO("can change optimization only once")
            }
            Ares::setOptimizationLevel(1);
            continue;
        }
        if (!strcmp(argv[i], "-O2")) {
            if (Ares::getOptimizationLevel() != 0) {
                TODO("can change optimization only once");
            }
            Ares::setOptimizationLevel(2);
            continue;
        }
        if (!strcmp(argv[i], "-O3")) {
            TODO("Aggresive optimizations to be added");
            continue;
        }
        if (!strcmp(argv[i], "-v") || !strcmp(argv[i], "--version") ) {
            TODO("Version system to be added")
            continue;
        }
        if (!strcmp(argv[i], "-Wall")) {
            Ares::setWarnings();
            continue;
        }
        if (!strcmp(argv[i], "-Werror")) {
            Ares::setWerrors();
            continue;
        }
        if (!strcmp(argv[i], "--print-ctx")) {
            Ares::setPrintCtx();
        }
        if (argv[i][0] == '-') {
            Ares::error(UNKNOWN_FLAG_ENCOUNTERED, argv[i]);
            continue;
        }
        // no -.. = file to read
        if (file_exists(argv[i])) {
            Ares::init(readFileToString(argv[i]));
            //Ares::add(argv[i])
            continue;
        }
        Ares::error(FILE_NOT_FOUND, argv[i]);
    }
    Ares::run();
    return 0;
}
