//
// Created by nikolas on 5/12/26.
//

#include "DTT.h"

#include <iostream>

std::unordered_map<std::string, DTTEntry> DTT::table = {
    {"int",{8, "dword"}}, // temporary
    {"short", {8, "word"}},
    {"long", {8, "qword"}}
};

int DTT::getSize(std::string type) {
    if (table.contains(type)) {
        return table[type].size;
    }
    return 0;
}

std::string DTT::getWordType(const std::string &name) {
    return table[name].wordType;
}
