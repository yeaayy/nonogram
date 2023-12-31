#ifndef NUMBER_PARSER_HPP
#define NUMBER_PARSER_HPP

#include <parser/parser.hpp>

class NumberParser : public Parser::Parser<int> {
    using stream = ::Parser::stream;
    using CharTable = ::Parser::CharTable;
    using ErrorHandler = ::Parser::ErrorHandler;

public:
    NumberParser(std::shared_ptr<ErrorHandler> errorHandler = nullptr);
    ~NumberParser();
    bool canParse(stream &stream) override;

protected:
    bool exec(stream &stream, int &result) override;

private:
    CharTable number;
};

#endif /* NUMBER_PARSER_HPP */
