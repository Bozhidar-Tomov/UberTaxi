#include "IdGenerator.h"

size_t IdGenerator::_id = 0;

size_t IdGenerator::getId() noexcept
{
    generateNext();
    return _id;
}

void IdGenerator::seed(size_t id) noexcept
{
    _id = id;
}

void IdGenerator::generateNext() noexcept
{
    ++_id;
}
