#include "Address.h"

Address::Address(const MyString &name, const MyString &description, double x, double y)
    : _name(name), _description(description), _coordinates(Point(x, y)) {}

Address::Address(MyString &&name, MyString &&description, double x, double y) noexcept
    : _name(std::move(name)), _description(std::move(description)), _coordinates(Point(x, y)) {}

double Address::getDist(const Address &other) const noexcept
{
    return _coordinates.getDist(other._coordinates);
}
