#pragma once
#include <iostream>
#include "MyString/MyString.h"

class Address
{
    struct Point
    {
        double _x = 0;
        double _y = 0;

        Point() = default;
        Point(double x, double y) : _x(x), _y(y) {}

        double getDist(const Point &other) const noexcept;
    };

    MyString _name;
    MyString _description;
    Point _coordinates;

public:
    Address() = default;
    Address(const Address &) = default;
    Address(Address &&) noexcept = default;
    Address &operator=(const Address &) = default;
    Address &operator=(Address &&) noexcept = default;

    Address(const MyString &, double, double, const MyString & = MyString(""));
    Address(MyString &&, double, double, MyString && = MyString("")) noexcept;
    ~Address() = default;

    double getDist(const Address &) const noexcept;

    friend std::ostream &operator<<(std::ostream &, const Address &);
    friend std::ostream &operator<<(std::ostream &, const Address::Point &);
};
