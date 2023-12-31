#include "number_parser.hpp"

using namespace ::Parser;

NumberParser::NumberParser(std::shared_ptr<ErrorHandler> errorHandler)
    : Parser(errorHandler)
{
    number = ::Parser::makeTable([](int x) {
        return x >= '0' && x <= '9';
    });
}

NumberParser::~NumberParser() {
    deleteTable(number);
}

bool NumberParser::canParse(stream &stream)
{
    return number[stream.peek()];
}

bool NumberParser::exec(stream &stream, int &result)
{
    auto start = stream.tellg();
    while(number[stream.peek()]) {
        stream.seek();
    }
    int length = stream.tellg() - start;
    if(length == 0) {
        return false;
    }
	char tmp[length + 1];
    stream.start(start);
    stream.read(tmp, length);
    tmp[length] = '\0';
    result = atoi(tmp);
    return true;
}