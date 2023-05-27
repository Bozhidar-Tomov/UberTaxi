#pragma once
#include <math.h>
#include "MyString/MyString.h"

class Address
{
    struct Point
    {
        double _x = 0;
        double _y = 0;

        Point(double x, double y) : _x(x), _y(y) {}

        double getDist(const Point &other) const noexcept
        {
            double dx = _x - other._x;
            double dy = _y - other._y;

            return sqrt(dx * dx + dy * dy);
        }
    };

    MyString _name;
    MyString _description;
    Point _coordinates;

public:
    Address(const MyString &, const MyString &, double, double);
    Address(MyString &&, MyString &&, double, double) noexcept;
    ~Address() = default;

    double getDist(const Address &) const noexcept;
};
