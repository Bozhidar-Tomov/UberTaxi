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

size_t strToSize_t(const char *str) noexcept
{
    size_t x = 0;
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

char *intToChar(int32_t num)
{
    static char buffer[50];
    int32_t i = 0;
    bool isNegative = false;

    if (num == 0)
    {
        buffer[i++] = '0';
        buffer[i] = '\0';
        return buffer;
    }

    if (num < 0)
    {
        isNegative = true;
        num = -num;
    }

    while (num != 0)
    {
        int32_t rem = num % 10;
        buffer[i++] = char(rem + '0');
        num = num / 10;
    }

    if (isNegative)
        buffer[i++] = '-';

    buffer[i] = '\0';

    int32_t start = 0;
    int32_t end = i - 1;
    while (start < end)
    {
        char temp = buffer[start];
        buffer[start] = buffer[end];
        buffer[end] = temp;
        start++;
        end--;
    }

    return buffer;
}