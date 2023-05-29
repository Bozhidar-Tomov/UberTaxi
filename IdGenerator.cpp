#include "IdGenerator.h"

size_t IdGenerator::id = 0;

size_t IdGenerator::getId() noexcept
{
    generateNext();
    return id;
}

void IdGenerator::generateNext() noexcept
{
    ++id;
}
