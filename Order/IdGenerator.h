#pragma once
#include <stddef.h>

class IdGenerator
{
    static size_t _id;

public:
    static size_t getId() noexcept;
    static void seed(size_t id) noexcept;

private:
    static void generateNext() noexcept;
};