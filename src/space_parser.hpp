#ifndef SPACE_PARSER_HPP
#define SPACE_PARSER_HPP

#include "parser/parser.hpp"

class SpaceParser : public Parser::Parser<void*> {
    using stream = ::Parser::stream;
    using CharTable = ::Parser::CharTable;
    using ErrorHandler = ::Parser::ErrorHandler;

public:
    SpaceParser(std::shared_ptr<ErrorHandler> errorHandler = nullptr);
    ~SpaceParser();
    bool canParse(stream &stream) override;

protected:
    bool exec(stream &stream, void *&result) override;

private:
    CharTable isSpace;
};

#endif /* SPACE_PARSER_HPP */
