#ifndef NUMBER_LIST_PARSER_HPP
#define NUMBER_LIST_PARSER_HPP

#include "parser/parser.hpp"
#include "number_parser.hpp"
#include "space_parser.hpp"

class NumberListParser : public Parser::Parser<int*> {
    using stream = ::Parser::stream;
    using CharTable = ::Parser::CharTable;
    using ErrorHandler = ::Parser::ErrorHandler;

public:
    NumberListParser(
        std::shared_ptr<SpaceParser> space = nullptr,
        std::shared_ptr<NumberParser> number = nullptr,
        std::shared_ptr<ErrorHandler> errorHandler = nullptr
    );
    bool canParse(stream &stream) override;

protected:
    bool exec(stream &stream, int *&result) override;

private:
    std::shared_ptr<SpaceParser> space;
    std::shared_ptr<NumberParser> number;
};

#endif /* NUMBER_LIST_PARSER_HPP */
