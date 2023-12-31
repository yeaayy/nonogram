#ifndef NONOGRAM_PARSER_HPP
#define NONOGRAM_PARSER_HPP

#include "nonogram.hpp"
#include "parser/parser.hpp"
#include "number_parser.hpp"
#include "space_parser.hpp"
#include "number_list_parser.hpp"

class NonogramParser : public Parser::Parser<Nonogram*> {
    using stream = ::Parser::stream;
    using CharTable = ::Parser::CharTable;
    using ErrorHandler = ::Parser::ErrorHandler;

public:
    NonogramParser(
        std::shared_ptr<SpaceParser> space = nullptr,
        std::shared_ptr<NumberParser> number = nullptr,
        std::shared_ptr<NumberListParser> numberList = nullptr,
        std::shared_ptr<ErrorHandler> errorHandler = nullptr
    );
    bool canParse(stream &stream) override;

protected:
    bool exec(stream &stream, Nonogram *&result) override;

private:
    std::shared_ptr<SpaceParser> space;
    std::shared_ptr<NumberListParser> numberList;
};

#endif /* NONOGRAM_PARSER_HPP */
