
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <cstring>

#include "nonogram_parser.hpp"
#include "nonogram.hpp"

std::ostream &operator<<(std::ostream &a, const std::stringstream &b) {
    return a << b.rdbuf();
}

int main(int argc, char const *argv[]) {
    NonogramParser parser;
    auto stream = Parser::stream(std::cin);
    Nonogram* nonogram;
    if(!parser.beginParse(stream, nonogram)) {
        return 1;
    }
    bool changed;
    do {
        changed = false;
        for(int y = 0; y < nonogram->getSize(); y++) {  
            for(int x = 0; x < nonogram->getSize(); x++) {
                if(nonogram->getType(x, y) != BoxType::UNKNOWN) continue;
                float col = nonogram->getColProbability(x, y);
                float row = nonogram->getRowProbability(x, y);
                if(col == 0 || row == 0) changed |= nonogram->collapse(x, y, BoxType::NONE);
                else if(col == 1 || row == 1) changed |= nonogram->collapse(x, y, BoxType::FILL);
            }
        }
    } while(changed);
    std::cout << nonogram;
    return 0;
}
