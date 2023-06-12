#pragma once
#include <stddef.h>
#include <cstdint>

bool areEqual(double, double) noexcept;
double absolute(double) noexcept;
size_t strToSize_t(const char *) noexcept;
double strToDouble(const char *) noexcept;
char *intToChar(int32_t);
