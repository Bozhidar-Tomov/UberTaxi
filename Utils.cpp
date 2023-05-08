#include "Utils.h"

bool areEqual(double x, double y) noexcept
{
    static const double EPSILON = 0.00001;

    return (absolute(x - y) < EPSILON);
}

double absolute(double x) noexcept
{
    return x < 0 ? -x : x;
}

int strToInt(const char *str) noexcept
{
    int x = 0;
    bool isNegative = (*str == '-');

    if (isNegative)
        ++str;

    while (*str >= '0' && *str <= '9')
    {
        x = (x << 3) + (x << 1) + (*str - '0');
        ++str;
    }

    return isNegative ? -x : x;
}

double strToDouble(const char *str) noexcept
{
    double x = 0;
    bool isNegative = (*str == '-');
    bool isDecimal = false;
    double decimalPlace = 1;

    if (isNegative)
        ++str;

    while ((*str >= '0' && *str <= '9') || *str == '.')
    {
        if (*str == '.')
        {
            isDecimal = true;
        }
        else
        {
            if (isDecimal)
                decimalPlace *= 10;
            x = x * 10 + (*str - '0');
        }
        ++str;
    }

    x /= decimalPlace;

    return isNegative ? -x : x;
}