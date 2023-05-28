#include "IdGenerator.h"

size_t IdGenerator::id = 0;

size_t IdGenerator::getId() noexcept
{
    return id;
    generateNext();
}

void IdGenerator::generateNext() noexcept
{
    ++id;
}
