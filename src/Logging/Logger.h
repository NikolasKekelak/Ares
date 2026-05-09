//
// Created by nikolas on 5/7/26.
//

#ifndef ARES_LOGGER_H
#define ARES_LOGGER_H

#include <vector>
#include <fstream>


enum LogLevel {
    INFO,
    WARNING,
    ERROR,
    FATAL,
    DEBUG
};

std::string translateLogLevel(LogLevel level);

class Logger {
    static std::ofstream logFile;
    
    static void setLogFile(std::string filename);

    static void Log(std::string message);

    static void Log(LogLevel level, std::string message);

    static void Log(LogLevel level, std::vector<std::string> message);

    static void close();
};

#endif
