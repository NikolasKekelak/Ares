#include <cstring>
#include <iostream>

#include "src/Lexer/Lexer.h"
#include "src/temp_testing/test_compile_tokens_to_asm.h"

#include <string>

#include "src/fileManager.h"
#include "src/Ares/Ares.h"


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
        if (!strcmp(argv[i], "--emit-all")) {
            Ares::setPrintASM();
            Ares::setPrintAST();
            Ares::setPrintTokens();
        }

        if (argv[i][0] == '-') {
            Ares::error(UNKNOWN_FLAG_ENCOUNTERED, argv[i]);
            continue;
        }
        // no -.. = file to read
        FileManager::addFile(argv[i]);
    }
    Ares::init();
    Ares::run();

    return 0;
}
