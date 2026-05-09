//
// Created by nikolas on 5/7/26.
//

#include "Logger.h"



std::string translateLogLevel(LogLevel level) {
    switch (level) {
        case DEBUG:
            return "DEBUG";
        case INFO:
            return "INFO";
        case WARNING:
            return "WARNING";
        case ERROR:
            return "ERROR";
        default: return "UNKNOWN_LOG_LEVEL";
    }
}

void Logger::setLogFile(std::string filename) {
    logFile.open(filename, std::ios::out | std::ios::app);
}

void Logger::Log(std::string message) {
    logFile << message << std::endl;
}

void Logger::Log(LogLevel level, std::string message) {
    logFile << "["<<translateLogLevel(level) << "] " << message << std::endl;
}

void Logger::Log(LogLevel level, std::vector<std::string> message) {
    logFile << "["<<translateLogLevel(level) << "] ";
    for (auto &m : message) {
        logFile << m << " ";
    }
    logFile << std::endl;
}

void Logger::close() {
    logFile.close();
}
