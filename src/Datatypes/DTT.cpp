//
// Created by nikolas on 5/12/26.
//

#include "DTT.h"

#include <iostream>

std::unordered_map<std::string, DTTEntry> DTT::table = {
    {"int",{4}},
    {"short", {2}},
    {"long", {8}}
};

int DTT::getSize(std::string type) {
    std::cout<<type<< " co to kurva "<< table[type].size <<std::endl;
    if (table.contains(type)) {
        return table[type].size;
    }
    return 0;
}
