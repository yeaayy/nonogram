#ifndef PARSER_PARSER_HPP
#define PARSER_PARSER_HPP

#include <sstream>
#include <memory>

#include "parser/error_handler.hpp"
#include "parser/stream.hpp"

namespace Parser {

typedef bool *CharTable;

class BaseParser
{
protected:
	bool error(stream &stream, int start, int end, const char *msgFmt, va_list args);
	bool error(stream &stream, int start, int end, const char *msgFmt, ...);
	bool error(int start, int end, const char *msgFmt, va_list args);
	bool error(int start, int end, const char *msgFmt, ...);

public:
    BaseParser(std::shared_ptr<ErrorHandler> errorHandler = nullptr);
    virtual ~BaseParser();

	virtual bool canParse(stream &stream);
    std::shared_ptr<ErrorHandler> &getErrorHandler();

private:
    std::shared_ptr<ErrorHandler> errorHandler;
};

template<typename T>
class Parser : public BaseParser
{
protected:
	// virtual bool exec(stream &stream, T &result) = 0;
	virtual bool exec(stream &stream, T &result) = 0;

public:
    Parser(std::shared_ptr<ErrorHandler> errorHandler = nullptr): BaseParser(errorHandler) {}

    virtual T parse(stream &stream)
    {
        T tmp;
        beginParse(stream, tmp);
        return tmp;
    }

	virtual bool beginParse(stream &stream, T &result)
    {
        auto start = stream.tellg();
        if(!exec(stream, result)) {
            stream.start(start);
            return false;
        }
        return true;
    }
};

CharTable makeTable(bool (*cond)(int));
void deleteTable(CharTable table);

} // namespace Parser

#endif /* PARSER_PARSER_HPP */