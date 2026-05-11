//
// Created by nikolas on 5/10/26.
//

#include "Ares.h"

#include "../AST/Parser.h"

AresContext Ares::context;
AresSettings Ares::settings;
Lexer Ares::lexer;

void Ares::init(std::string inputFile) {
    Logger::setLogFile(context.logFile);
    lexer.setSource(inputFile);
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

    if (!settings.compile)
        exit(0);

    int optimization_level = settings.optimizationLevel;
    std::cout << "Optimization level: " << optimization_level << std::endl;
    if (optimization_level < 0) {
        TODO("AST -> Source code")
    }

    TODO("Compilation using IR is not defined yet")
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

void Ares::error(ErrorCode code, ErrorToken token) {
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
