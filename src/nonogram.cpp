#include "nonogram.hpp"

#include <functional>

namespace {

std::stringstream bg(int color) {
    std::stringstream stream;
    int r = (color >> 16) & 0xff;
    int g = (color >>  8) & 0xff;
    int b = (color >>  0) & 0xff;
    stream << "\e[48;2;" << r << ";" << g << ";" << b << "m";
    return stream;
}

std::stringstream printProbability(int size, std::function<float(int x, int y)> getProbability) {
    std::stringstream stream;
    for(int y = 0; y < size; y++) {
        for(int x = 0; x < size; x++) {
            int grey = getProbability(x, y) * 255;
            if(grey == 255) {
                stream << "\e[m[]";
            } else if(grey == 0) {
                stream << "\e[m..";
            } else {
                stream << bg(grey << 16 | grey << 8 | grey).rdbuf() << "  ";
            }
        }
        stream << "\e[m\n";
    }
    return stream;
}

} // namespace

Nonogram::Nonogram(std::vector<int*> &rowCue, std::vector<int*> &colCue) {
    size = rowCue.size();
    grid = new BoxType[size * size];
    this->rowCue = new Cue[size];
    this->colCue = new Cue[size];

    std::fill(grid, grid + size * size, BoxType::UNKNOWN);
    for(int i = 0; i < size; i++) {
        this->rowCue[i] = Cue(this, CollapseSource::Row, i, size, rowCue[i]);
    }
    for(int i = 0; i < size; i++) {
        this->colCue[i] = Cue(this, CollapseSource::Col, i, size, colCue[i]);
    }

    for(int i = 0; i < size; i++) {
        auto cue = &this->rowCue[i];
        if(cue->isTrivial()) {
            cue->generatePosibility();
            collapseRow(i, cue->getPosibility().front());
        }
    }
    for(int i = 0; i < size; i++) {
        auto cue = &this->colCue[i];
        if(cue->isTrivial()) {
            cue->generatePosibility();
            collapseCol(i, cue->getPosibility().front());
        }
    }
    for(int i = 0; i < size; i++) {
        this->rowCue[i].generatePosibility();
        this->colCue[i].generatePosibility();
    }
}

Nonogram::~Nonogram() {
    delete[] grid;
    delete[] rowCue;
    delete[] colCue;
}

BoxType &Nonogram::getType(int x, int y) {
    return grid[y * size + x];
}

int Nonogram::getSize() {
    return size;
}

std::ostream &operator<<(std::ostream &os, Nonogram *nonogram) {
    const int size = nonogram->size;
    for(int y = 0; y < size; y++) {
        for(int x = 0; x < size; x++) {
            const char *str;
            switch(nonogram->getType(x, y)) {
                case BoxType::ERROR: str = "??"; break;
                case BoxType::FILL: str = "[]"; break;
                case BoxType::NONE: str = ".."; break;
                case BoxType::UNKNOWN: str = "  "; break;
            }
            os << str;
        }
        os << '\n';
    }
    return os;
}

float Nonogram::getRowProbability(int x, int y) {
    return rowCue[y].getProbability()[x];
}

float Nonogram::getColProbability(int x, int y) {
    return colCue[x].getProbability()[y];
}

std::stringstream Nonogram::rowCueProbability() {
    return printProbability(size, [this](int x, int y){
        return this->getRowProbability(x, y);
    });
}

std::stringstream Nonogram::colCueProbability() {
    return printProbability(size, [this](int x, int y){
        return this->getColProbability(x, y);
    });
}

bool Nonogram::collapse(int x, int y, BoxType value) {
    getType(x, y) = value;
    return rowCue[y].collapse(x, value)
        || colCue[x].collapse(y, value);
}

bool Nonogram::collapseCol(int index, BoxType *values) {
    bool result = false;
    for(int i = 0; i < size; i++) {
        auto &type = getType(index, i);
        if(type != BoxType::UNKNOWN) continue;
        type = values[i];
        result |= rowCue[i].collapse(index, values[i]);
    }
    return result;
}

bool Nonogram::collapseRow(int index, BoxType *values) {
    bool result = false;
    for(int i = 0; i < size; i++) {
        auto &type = getType(i, index);
        if(type != BoxType::UNKNOWN) continue;
        type = values[i];
        result |= colCue[i].collapse(index, values[i]);
    }
    return result;
}