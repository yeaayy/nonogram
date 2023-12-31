#include "nonogram_parser.hpp"

NonogramParser::NonogramParser(
    std::shared_ptr<SpaceParser> space,
    std::shared_ptr<NumberParser> number,
    std::shared_ptr<NumberListParser> numberList,
    std::shared_ptr<ErrorHandler> errorHandler
): Parser(errorHandler), space(space), numberList(numberList) {
    if(space == nullptr) {
        this->space = std::make_shared<SpaceParser>(getErrorHandler());
    }
    if(number == nullptr) {
        number = std::make_shared<NumberParser>(getErrorHandler());
    }
    if(numberList == nullptr) {
        this->numberList = std::make_shared<NumberListParser>(space, number, getErrorHandler());
    }
}


bool NonogramParser::canParse(stream &stream) {
    return true;
}

bool NonogramParser::exec(stream &stream, Nonogram *&result) {
    int start = stream.tellg();
    int *line = nullptr;
    std::vector<int*> rowCue;
    std::vector<int*> colCue;
    while(numberList->canParse(stream)) {
        numberList->beginParse(stream, line);
        rowCue.push_back(line);
    }

    space->parse(stream);
    if(stream.peek() == ';') {
        stream.seek();
    } else {
        return 1;
    }
    space->parse(stream);
    if(stream.peek() == '\n') {
        stream.seek();
    } else {
        return 1;
    }
    space->parse(stream);
    while(numberList->canParse(stream)) {
        numberList->beginParse(stream, line);
        colCue.push_back(line);
    }
    bool returnResult = true;
    if(rowCue.size() != colCue.size()) {
        returnResult = error(start, stream.tellg(), "Row size and column size doesn't match. row size=%d, column size=%d", rowCue.size(), colCue.size());
    } else {
        result = new Nonogram(rowCue, colCue);
    }
    return returnResult;
}
