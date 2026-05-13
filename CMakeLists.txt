cmake_minimum_required(VERSION 4.2)
project(Ares)

set(CMAKE_CXX_STANDARD 20)

add_executable(Ares main.cpp
        src/Lexer/Lexer.h
        src/Logging/Logger.h
        src/Logging/Logger.cpp
        src/temp_testing/test_compile_tokens_to_asm.h
        src/Tokens/Token.h
        src/Tokens/Token.cpp
        src/Lexer/Lexer.cpp
        src/myHeaders.h
        src/Ares/Ares.cpp
        src/Ares/Ares.h
        src/ErrorHandling/ErrorHandler.cpp
        src/ErrorHandling/ErrorHandler.h
        src/AST/Parser.cpp
        src/AST/Parser.h
        src/AST/Node.cpp
        src/AST/Node.h
        src/CodeGen/CodeGen.cpp
        src/CodeGen/CodeGen.h
        src/Datatypes/DTT.cpp
        src/Datatypes/DTT.h
        src/fileManager.cpp
        src/fileManager.h
        src/utils.h
)
