//
// Created by nikolas on 5/13/26.
//

#ifndef ARES_UTILS_H
#define ARES_UTILS_H
#include <sstream>

inline std::string readFileToString(const std::string &filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

#endif //ARES_UTILS_H
