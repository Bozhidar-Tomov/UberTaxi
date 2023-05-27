#pragma once
#include <math.h>
#include "MyString/MyString.h"

class Address
{
    struct Point
    {
        double _x = 0;
        double _y = 0;

        Point(double x, double y) : _x(x), _y(y){};

        double getDist(const Point &other) const
        {
            double dx = _x - other._x;
            double dy = _y - other._y;

            return sqrt(dx * dx + dy * dy);
        }
    };

    MyString _name;
    Point _coordinates;
    MyString _description;

public:
    Address(const MyString &, double, double, const MyString &);
    Address(MyString &&, double, double, MyString &&) noexcept;
    ~Address() = default;

    double getDist(const Address &) const;
};
