//
// Created by nikolas on 5/12/26.
//

#ifndef ARES_DTT_H
#define ARES_DTT_H
#include <string>
#include <unordered_map>


struct DTTEntry {
    int size; // in bytes
    std::string wordType;
};

// Data type table
class DTT {
    static std::unordered_map<std::string, DTTEntry> table;
public:
    static int getSize(std::string type);

    static std::string getWordType(const std::string &string);
};



#endif //ARES_DTT_H
