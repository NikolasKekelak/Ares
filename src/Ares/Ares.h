//
// Created by nikolas on 5/10/26.
//

#ifndef ARES_ARES_H
#define ARES_ARES_H
#include <string>

#include "../ErrorHandling/ErrorHandler.h"
#include "../Logging/Logger.h"
#include "../Tokens/Token.h"
#include "../Lexer/Lexer.h"
#include "../CodeGen/CodeGen.h"

struct AresContext {

    std::string logFile    = "log";
    std::string helpFile   = "help";
    std::string configFile = "config";
    std::string asmFile    = "out.asm";
    std::string oFile      = "out.o";
    std::string outFile    = "a";

    // std::vector<std::string> inputFiles;
    std::string inputFile;
};

struct AresSettings {

    bool printTokens = false;
    bool printAST = false;
    bool printASM = false;
    bool printIR = false;

    bool compile = true;

    bool optimizationChange = false;
    int optimizationLevel = 0; // -1 no optimizations, 0 default, 1 minor optimization, 2 major optimization, 3 aggresive optimization

    bool warnings = false;
    bool werrors  = false;

    bool printCtx = false;
};

class Ares {
    static AresContext context;
    static AresSettings settings;
    static Lexer lexer;

public:
    static void init();

    static void close();

    static void terminate();

    static void run();

    static void help();

    static void error(ErrorCode code);

    static void error(ErrorCode code, const std::string& msg);
    static void error(ErrorCode code, const std::string &msg, ErrorToken token);

    static void error(std::vector<std::string> &msg);

    static void error(ErrorCode code, const ErrorToken &token);

    static void setOutputFile(const std::string &filename);
    static void setPrintTokens();
    static void setPrintAST();
    static void setPrintASM();
    static void setPrintIR();
    static void setNoCompile();
    static void setOptimizationLevel(int level);
    static int  getOptimizationLevel();

    static void setWarnings();
    static void setWerrors();

    static void setPrintCtx();
    static void printCtx();
};


#endif //ARES_ARES_H
