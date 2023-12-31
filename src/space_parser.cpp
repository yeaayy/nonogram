#include "space_parser.hpp"

using namespace ::Parser;

SpaceParser::SpaceParser(std::shared_ptr<ErrorHandler> errorHandler)
    : Parser(errorHandler)
{
    isSpace = makeTable([](int x) {
        return x == ' ' || x == '\t';
    });
}

SpaceParser::~SpaceParser()
{
    deleteTable(isSpace);
}

bool SpaceParser::canParse(stream &stream)
{
    return isSpace[stream.peek()];
}

bool SpaceParser::exec(stream &stream, void *&result)
{
    while(isSpace[stream.peek()]) {
        stream.seek();
    }
    return true;
}
