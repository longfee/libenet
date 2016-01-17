#ifndef LIBFEI_BUFFER_H
#define LIBFEI_BUFFER_H

#include <string>

/**
 * Buffer  |--1----2----|
*/

class Buffer{
public:
	Buffer(int capacity);
	~Buffer();

	int append(const char* data, int len);

	int append(const std::string& data);

	int appendInt(int data);

	int appendDouble(double data);

	int readFd(int fd);

	int capacity();

	int readable();

	int writeable();

	int clear();

	const char* peek(int);

	int peekAsString(std::string& data);

private:

	int read_;
	int write_;
	int capacity_;

};

#endif
