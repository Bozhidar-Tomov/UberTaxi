#pragma once
#include <cstdint>

void myStrCpy(char *, const char *, size_t = 0);
size_t myStrLen(const char *);
int64_t resizeUtil(char *&, size_t, bool = false);
int16_t myStrCmp(const char *, const char *);