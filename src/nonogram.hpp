#ifndef NONOGRAM_HPP
#define NONOGRAM_HPP

#include <ostream>
#include <sstream>
#include <vector>

#include "cue.hpp"

class Nonogram {
public:
    Nonogram(std::vector<int*> &rowCue, std::vector<int*> &colCue);
    ~Nonogram();
    BoxType &getType(int x, int y);
    int getSize();
    bool collapse(int x, int y, BoxType value);
    bool collapseRow(int index, BoxType *values);
    bool collapseCol(int index, BoxType *values);
    float getRowProbability(int x, int y);
    float getColProbability(int x, int y);
    std::stringstream rowCueProbability();
    std::stringstream colCueProbability();
    friend std::ostream &operator<<(std::ostream &os, Nonogram *nonogram);

private:
    int size;
    Cue *rowCue;
    Cue *colCue;
    BoxType *grid;
};

#endif /* NONOGRAM_HPP */
