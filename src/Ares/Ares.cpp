//
// Created by nikolas on 5/10/26.
//

#include "Ares.h"

#include <utility>

#include "../AST/Parser.h"

#define PPRINT(msg, val) std::cout << GREEN msg RESET << val << std::endl;


AresContext Ares::context;
AresSettings Ares::settings;
Lexer Ares::lexer;

void Ares::init(std::string inputFile) {
    Logger::setLogFile(context.logFile);
    lexer.setSource(std::move(inputFile));
}

void Ares::close() {
    Logger::close();
}

void Ares::terminate() {
    close();
    std::cout << "compilation terminated\n";
    exit(0);
}

void Ares::run() {
    lexer.scanTokens();
    if (settings.printTokens) {
        for (auto it: lexer.getTokens()) {
            it.print();
            std::cout << std::endl;
        }
    }

    // Parse AST
    Parser parser(lexer.getTokens());
    auto program = parser.parseProgram();


    if (settings.printAST) {
        program->print(0);
    }



    int optimization_level = settings.optimizationLevel;
    if (optimization_level < 0) {
        CodeGen codeGen;
        codeGen.generateCode(context.asmFile, std::move(program));
        if (settings.printASM) {
            std::string command = "cat "+context.asmFile;
            system(command.c_str());
        }
        if (!settings.compile) {
            terminate();
        }

        system("make");
        exit(0);
    }

    if (!settings.compile) {
        terminate();
    }

    if (optimization_level >= 1) {
        TODO("Constant folding, dead code removal")
    }

    if (optimization_level >= 2) {
        TODO("Register reusal, packing")
    }

    if (optimization_level >= 3) {
        TODO("How did we get here")
    }
    // Code gen
}

void Ares::help() {
    std::ifstream helpFile(context.helpFile);
    while (helpFile.good()) {
        std::string line;
        std::getline(helpFile, line);
        std::cout << line << std::endl;
    }
}

void Ares::error(ErrorCode code) {
    ErrorHandler::handleError(code);
}

void Ares::error(ErrorCode code, const std::string &msg) {
    ErrorHandler::setErrorString(msg);
    ErrorHandler::handleError(code);
}

void Ares::error(ErrorCode code, const std::string &msg, ErrorToken token) {
    ErrorHandler::setErrorString(msg);
    ErrorHandler::setErrorToken(token);
    ErrorHandler::handleError(code);
}


void Ares::error(std::vector<std::string> &msg) {
    Logger::Log(ERROR, msg);
}

void Ares::error(ErrorCode code, const ErrorToken &token) {
    TODO("Remove this function")
    switch (code) {
        case UNKNOWN_CHARACTER_ENCOUNTERED:
            printf("Unknown character encountered at line %d, column %d: %s\n", token.line, token.column,
                   token.literal.c_str());
            break;
    }
}

void Ares::setOutputFile(const std::string &filename) {
    context.outFile = filename;
}

void Ares::setPrintTokens() {
    settings.printTokens = true;
}

void Ares::setPrintAST() {
    settings.printAST = true;
}

void Ares::setPrintASM() {
    settings.printASM = true;
}

void Ares::setPrintIR() {
    settings.printIR = true;
}

void Ares::setNoCompile() {
    settings.compile = false;
}

void Ares::setOptimizationLevel(int level) {
    settings.optimizationLevel = level;
}

int Ares::getOptimizationLevel() {
    return settings.optimizationLevel;
}

void Ares::setWarnings() {
    // if (settings.warnings) {
    //     Ares::error(WARNINGS_FLAG_ALREADY_SET);
    // }
    // if (settings.werrors) {
    //     Ares::error(WERRORS_INSTEAD_OF_WARNINGS);
    // }
    settings.warnings = true;
}

void Ares::setWerrors() {
    // if (settings.warnings) {
    //     Ares::error(WARNINGS_INSTEAD_OF_WERRORS);
    // }
    // if (settings.werrors) {
    //     Ares::error(WERRORS_FLAG_ALREADY_SET);
    // }
    settings.werrors = true;
}

void Ares::setPrintCtx() {
    settings.printCtx = true;


void Ares::printCtx() {
    std::cout <<RED "Ares settings and context" RESET<<std::endl;
    PPRINT("Log file: ", context.logFile );
    PPRINT("Help file: ", context.helpFile );
    PPRINT("Config file: ", context.configFile );
    PPRINT("Asm file: ", context.asmFile );
    PPRINT("Output name: ", context.outFile );
    std::cout << std::endl;
}
