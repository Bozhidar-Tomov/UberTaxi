#include "file_stream_error.h"

file_stream_error::file_stream_error(const char *msg, const char *fileName) : std::runtime_error(msg)
{
    _fileName = fileName;
}