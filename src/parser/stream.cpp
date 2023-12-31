#include "parser/stream.hpp"

#include <cstdlib>
#include <cstring>
#include <sstream>

namespace Parser {

stream::stream(const char *buffer)
    : stream(strlen(buffer), strdup(buffer))
{}

stream::stream(std::istream &stream)
    : index(0)
{
    stream.seekg(0, std::ios::end);
    std::streampos length;
    if(stream) {
        length = stream.tellg();
        stream.seekg(0,std::ios::beg);
        // std::vector<char> buffer(length);
        // stream.read(&buffer[0],length);
        // str.rdbuf()->pubsetbuf(&buffer[0],length);
        buffer = (char*) malloc(length + (std::streampos) 1);
        stream.read(buffer, length);
    } else {
        std::stringstream str;
        stream.clear();
        str << stream.rdbuf();
        length = str.tellp();
        buffer = (char*) malloc(length + (std::streampos) 1);
        stream.read(buffer, length);
    }
    buffer[length] = '\0';
    this->len = length;
}

stream::stream(int size, char *buffer)
	: buffer((char*) buffer), index(0), len(size)
{}

stream::~stream() {
    free(buffer);
}

int stream::get()
{
	return eof() ? -1 : buffer[index++];
}

void stream::read(void *dst, int len)
{
	memcpy(dst, &buffer[index], len);
    index += len;
}

int stream::peek(int n)
{
	return eof(n) ? -1 : buffer[index + n];
}

bool stream::eof(int n)
{
	return (index + n) >= len;
}

int stream::tellg()
{
	return index;
}

void stream::seek(int n)
{
	index += n;
}

void stream::start(int n)
{
	index = n;
}

void stream::end(int n)
{
	index = len + n;
}

bool operator==(const stream &stream1, const stream &stream2) {
    return stream1.buffer == stream2.buffer;
}

} // namespace Parser
