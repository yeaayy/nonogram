#include "parser/error_handler.hpp"

namespace Parser {

ErrorHandler::ErrorHandler()
{
    this->message = nullptr;
}

ErrorHandler::~ErrorHandler()
{
    if(message != nullptr) {
        free(message);
    }
}

void ErrorHandler::reportError(std::streampos start, std::streampos end, const char *msgFmt, va_list messageData)
{
    this->start = start;
    this->end = end;
    if(message != nullptr) {
        free(message);
    }
    vasprintf(&message, msgFmt, messageData);
    for(auto handler : onErrors) {
        handler(this);
    }
}

void ErrorHandler::clearOnError()
{
    // for(int i = 0; i < onErrors.size(); i++) {
    //     delete onErrors.value(i);
    // }
    onErrors.clear();
}

void ErrorHandler::addOnError(OnError handler)
{
    onErrors.push_back(handler);
}

// bool ErrorHandler::removeOnError(void *tag)
// {
//     int index = onErrors.indexOf(tag);
//     if(index != -1) {
//         delete onErrors.value(index);
//         onErrors.remove(index);
//         return true;
//     }
//     return false;
// }

// int ErrorHandler::getMessageId()
// {
//     return messageId;
// }

std::streampos ErrorHandler::getErrorStart()
{
    return start;
}

std::streampos ErrorHandler::getErrorEnd()
{
    return end;
}

const char *ErrorHandler::getMessage()
{
    return message;
}


std::string ErrorHandler::format(std::stringstream &stream, bool color)
{
    std::stringstream result;
    
    stream.seekg(0, std::ios::end);
    std::streampos length = stream.tellg();

    std::streampos start = this->start, end = this->end;
    std::streampos left = start, right = end;
    stream.seekg(left, std::ios::beg);
    while(left > 0 && stream.peek() != '\n') {
        left -= 1;
        stream.seekg(left, std::ios::beg);
    }

    stream.seekg(right, std::ios::beg);
    while(right < length && stream.good() && stream.peek() != '\n') {
        right += 1;
        stream.seekg(right, std::ios::beg);
    }
    
    {
        stream.seekg(left, std::ios::beg);
        int size = right - left;
        char tmp[size];
        stream.read(tmp, size);
        result << tmp;
    }
    // while(left > 0 && tmp[left - 1] && tmp[left - 1] != '\n') left--;
    // while(right < len && tmp[right] && tmp[right] != '\n') right++;
    // tmp[right] = '\0';
    // fputs(tmp + left, dst);
    // fputc('\n', dst);

    int space = start - left;
    int marker = end -  start;
    while(space--) result << ' ';
    while(marker--) result << '^';
    // fputc('\n', dst);
    result << '\n';
    return result.str();
}

// void ErrorHandler::printLine(FILE *dst, File *inp)
// {
//     inp->seekEnd(0);
//     int len = inp->offset();
//     char tmp[len+1];
//     inp->seekSet(0);
//     inp->read(tmp, len);
//     tmp[len] = '\0';

//     int start = this->start, end = this->end;
//     int left = start, right = end;
//     while(left > 0 && tmp[left - 1] && tmp[left - 1] != '\n') left--;
//     while(right < len && tmp[right] && tmp[right] != '\n') right++;
//     tmp[right] = '\0';
//     fputs(tmp + left, dst);
//     fputc('\n', dst);

//     int space = start - left;
//     int marker = end -  start;
//     while(space--) fputc(' ', dst);
//     while(marker--) fputc('^', dst);
//     fputc('\n', dst);
// }

// void ErrorHandler::printMessage(FILE *dst, bool color)
// {
//     if(color) {
//         printf("\e[31mError\e[m: %s\n", message);
//     } else {
//         printf("Error: %s\n", message);
//     }
// }

} // namespace Parser
