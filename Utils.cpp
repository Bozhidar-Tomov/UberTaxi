#include "Utils.h"

bool inline areEqual(double x, double y) noexcept
{
    static const double EPSILON = 0.00001;

    return (absolute(x - y) < EPSILON);
}

double inline absolute(double x) noexcept
{
    return x < 0 ? -x : x;
}