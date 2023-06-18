#include <math.h>
#include "Address.h"
#include "constants.h"

Address::Address(const MyString &name, double x, double y, const MyString &description)
    : _name(name), _description(description), _coordinates(Point(x, y)) {}

Address::Address(MyString &&name, double x, double y, const MyString &&description) noexcept
    : _name(std::move(name)), _description(std::move(description)), _coordinates(Point(x, y)) {}

double Address::getDist(const Address &other) const noexcept
{
    return _coordinates.getDist(other._coordinates);
}

std::ostream &operator<<(std::ostream &out, const Address &obj)
{
    if (&out == &std::cout)
        return out << "name: " << obj._name << ", description: " << obj._description;

    return out << obj._name << DELIM
               << obj._description << DELIM
               << obj._coordinates;
}

double Address::Point::getDist(const Point &other) const noexcept
{
    double dx = _x - other._x;
    double dy = _y - other._y;

    return sqrt(dx * dx + dy * dy);
}

std::ostream &operator<<(std::ostream &out, const Address::Point &obj)
{
    return out << obj._x << DELIM << obj._y;
}