#include "number_list_parser.hpp"


NumberListParser::NumberListParser(
    std::shared_ptr<SpaceParser> space,
    std::shared_ptr<NumberParser> number,
    std::shared_ptr<ErrorHandler> errorHandler
) : Parser(errorHandler), space(space), number(number)
{
    if(space == nullptr) {
        this->space = std::make_shared<SpaceParser>(getErrorHandler());
    }
    if(number == nullptr) {
        this->number = std::make_shared<NumberParser>(getErrorHandler());
    }
}

bool NumberListParser::canParse(stream &stream)
{
    return number->canParse(stream);
}

bool NumberListParser::exec(stream &stream, int *&result)
{
    std::list<int> tmp;
    int value;
    while(number->canParse(stream)) {
        if(!number->beginParse(stream, value)) {
            return false;
        }
        space->parse(stream);
        tmp.push_back(value);
    }
    if(stream.peek() == '\n') {
        stream.seek();
    } else if(stream.eof()){
    } else {
        return false;
    }
    if(tmp.size() == 0) {
        return false;
    }
    result = new int[tmp.size() + 1];
    std::copy(tmp.begin(), tmp.end(), result);
    result[tmp.size()] = 0;
    return true;
}
