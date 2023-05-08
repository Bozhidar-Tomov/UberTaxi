#pragma once
#include <stdexcept> // include std::exception

class file_stream_error : std::runtime_error
{
    const char *_fileName = nullptr;

public:
    file_stream_error(const char *, const char *);
};