#pragma once
#include <stddef.h>

class IdGenerator
{
    static size_t id;

public:
    static size_t getId() noexcept;

private:
    static void generateNext() noexcept;
};