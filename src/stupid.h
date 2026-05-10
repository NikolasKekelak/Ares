//
// Created by nikolas on 5/4/26.
//

#ifndef ATHENA_STUPID_H
#define ATHENA_STUPID_H

#include <cstdio>
#include <fstream>
#include <iosfwd>
#include <string>
#include <unordered_map>


#ifdef LOGGING

enum LogLevel {
    DEBUG, INFO, WARN, ERROR
};

class Logger {
    inline static std::ofstream log;
    inline static std::unordered_map<LogLevel, std::string> level_to_str = {
        {INFO, "INFO"},
        {WARN, "WARN"},
        {ERROR, "ERROR"},
        {DEBUG, "DEBUG"},

    };
public:
    inline static void init(const char *filename) {
        log.open(filename);
    }
    inline static void log_msg(LogLevel level, std::string msg) {
        log<< level_to_str[level] << ": " << msg << std::endl;
    }
    inline static void close() {
        log.close();
    }
};

#define LOG_INIT(file) Logger::init(file);
#define LOG(level,msg) Logger::log_msg(level,msg);
#define LOG_CLOSE      Logger::close();
#else
#define LOG_INIT(file)
#define LOG(level,msg)
#define LOG_CLOSE
#endif



#ifdef TODO_SIMPLE
#include <cstdio>
#define TODO(msg) do {fprintf(stderr,"TODO: %s: %d %s", __FILE__, __LINE__, msg); exit(1); }while(0);
#endif


#ifdef TODO_PRIORITY

#include <iostream>
#include <queue>
#include <string>
#include <tuple>

class Todo {
    struct Item {
        int priority;
        std::string msg;
        std::string file;
        int line;
    };

    struct Compare {
        bool operator()(const Item& a, const Item& b) const {
            return a.priority < b.priority; // higher priority first
        }
    };

    inline static std::priority_queue<Item, std::vector<Item>, Compare> todo_queue;

public:
    inline static void todo(std::string msg, int priority, std::string file, int line) {
        todo_queue.push(Item{
            priority,
            std::move(msg),
            std::move(file),
            line
        });
    }

    inline static void print_todo() {
        std::cout << "___________________TODO___________________\n";

        auto copy = todo_queue;

        while (!copy.empty()) {
            const auto& item = copy.top();

            std::cout
                << "[" << item.priority << "] "
                << item.file << ": "
                << item.line << " "
                << item.msg << "\n";

            copy.pop();
        }
    }
};

#define TODO(msg, priority) Todo::todo(msg, priority, __FILE__, __LINE__)
#define TODO_PRINT Todo::print_todo()
#endif

#endif //ATHENA_STUPID_H
