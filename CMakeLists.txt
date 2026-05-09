cmake_minimum_required(VERSION 4.2)
project(Ares)

set(CMAKE_CXX_STANDARD 20)

add_executable(Ares main.cpp
        src/Lexer/Lexer.h
        #src/Logging/Logger.h
        #src/Logging/Logger.cpp
        src/temp_testing/test_compile_tokens_to_asm.h
        src/Tokens/Token.h
        src/Tokens/Token.cpp
        src/Lexer/Lexer.cpp
        src/myHeaders.h
)
