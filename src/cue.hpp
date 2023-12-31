#ifndef CUE_HPP
#define CUE_HPP

#include <list>

class Nonogram;

enum class BoxType {
    ERROR,
    NONE,
    FILL,
    UNKNOWN,
};

enum class CollapseSource {
    Row,
    Col
};

class Cue {
public:
    Cue();
    Cue(Nonogram *parent, CollapseSource type, int index, int size, int *cues);
    ~Cue();
    bool collapse(int index, BoxType value);
    const float * getProbability();
    void generatePosibility();
    std::list<BoxType*> &getPosibility();
    const int *getBlockLengths();
    int getBlockSize();
    bool isTrivial();

private:
    Nonogram *parent;
    int size;
    CollapseSource type;
    int index;
    float *probability;
    int blockSize;
    int *blocks;
    std::list<BoxType*> posibility;

    void updateProbability();
};

#endif /* CUE_HPP */
