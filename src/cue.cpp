#include "cue.hpp"

#include <algorithm>

#include "nonogram.hpp"

namespace {

void generateAllCue0(std::list<BoxType*> &result, int size, int *blockLengths, int shift, int minSpace, const BoxType *parent) {
    const int currentBlockLength = blockLengths[0];
    const int nextBlockLength = blockLengths[1];
    if(nextBlockLength != 0) {
        for(int i = shift; i < size - minSpace + 1; i++) {
            BoxType *tmp = new BoxType[size];
            std::copy(parent, parent + size, tmp);
            std::fill(tmp + i, tmp + i + currentBlockLength, BoxType::FILL);
            generateAllCue0(result, size, blockLengths + 1, i + currentBlockLength + 1, minSpace - currentBlockLength - 1, tmp);
        }
    } else {
        for(int i = shift; i < size - minSpace + 1; i++) {
            BoxType *tmp = new BoxType[size];
            std::copy(parent, parent + size, tmp);
            std::fill(tmp + i, tmp + i + currentBlockLength, BoxType::FILL);
            result.push_back(tmp);
        }
    }
}

void generateAllCue(std::list<BoxType*> &result, int size, int *blockLengths) {
    int minSpace = 0;
    BoxType *origin = new BoxType[size];
    std::fill(origin, origin + size, BoxType::NONE);
    for(int i = 0; blockLengths[i]; i++) {
        minSpace += blockLengths[i];
        if(i > 0) minSpace++;
    }
    generateAllCue0(result, size, blockLengths, 0, minSpace, origin);
}

} // namespace

Cue::Cue() {
}

Cue::Cue(Nonogram *parent, CollapseSource type, int index, int size, int *cues): parent(parent), size(size), type(type), index(index) {
    this->probability = new float[size];
    this->blocks = cues;
}

Cue::~Cue() {
}

void Cue::generatePosibility() {
    generateAllCue(posibility, size, blocks);
    updateProbability();
}

std::list<BoxType*> &Cue::getPosibility() {
    return posibility;
}

bool Cue::collapse(int index, BoxType value) {
    auto originLength = posibility.size();
    if(originLength <= 1) {
        return false;
    }
    posibility.erase(std::remove_if(posibility.begin(), posibility.end(), [index, value](BoxType *one){
        return one[index] != value;
    }), posibility.end());
    if(posibility.size() == 0) {
        return false;
    } else if(posibility.size() == 1) {
        updateProbability();
        switch(type) {
        case CollapseSource::Col:
            parent->collapseCol(this->index, posibility.front());
            break;
        case CollapseSource::Row:
            parent->collapseRow(this->index, posibility.front());
            break;
        }
        return true;
    } else if(posibility.size() != originLength) {
        updateProbability();
        return true;
    }
    return false;
}

const float *Cue::getProbability() {
    return probability;
}

void Cue::updateProbability() {
    std::fill(probability, probability + size, 0);
    for(auto one : posibility) {
        for(int i = 0; i < size; i++) {
            if(one[i] == BoxType::FILL) probability[i]++; 
        }
    }
    for(int i = 0; i < size; i++) {
        probability[i] /= posibility.size();
    }
}

bool Cue::isTrivial() {
    int sum = -1;
    for(int i = 0; blocks[i]; i++) {
        sum += blocks[i];
        sum ++;
    }
    return sum == size;
}

const int *Cue::getBlockLengths() {
    return blocks;
}

int Cue::getBlockSize() {
    int result = 0;
    while(blocks[result])
        result++;
    return result;
}
