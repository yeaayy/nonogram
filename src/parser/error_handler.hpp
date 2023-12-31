#ifndef PARSER_ERROR_HANDLER_HPP
#define PARSER_ERROR_HANDLER_HPP

#include <list>
#include <sstream>
#include <string>
#include <functional>

namespace Parser {

class ErrorHandler;

// typedef void (*OnError)(ErrorHandler*);
typedef std::function<void(ErrorHandler*)> OnError;

class ErrorHandler
{
public:
    ErrorHandler();
    ~ErrorHandler();
    void clearOnError();
    void addOnError(OnError onError);
    // bool removeOnError(void *tag);
    int getMessageId();
    const char *getMessage();
    std::streampos getErrorStart();
    std::streampos getErrorEnd();
    std::string format(std::stringstream &stream, bool color = false);
    // std::string getLine(std::stringstream &stream);
    // std::string getMessage(std::stringstream &stream, bool color = false);

    // void printLine(FILE *dst, File *file);
    // void printMessage(FILE *dst, bool color = false);
    void reportError(std::streampos start, std::streampos end, const char *msgFmt, va_list messageData);

private:
    std::streampos start;
    std::streampos end;
    char *message;
    std::list<OnError> onErrors;
    // List<OnError*> onErrors;
    // std::map<void*, OnError*> onErrors;
};

} // namespace Parser

#endif /* PARSER_ERROR_HANDLER_HPP */
