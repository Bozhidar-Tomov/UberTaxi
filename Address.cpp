#include "Address.h"

Address::Address(const MyString &name, double x, double y, const MyString &description)
    : _name(name), _description(description), _coordinates(Point(x, y)) {}

Address::Address(MyString &&name, double x, double y, const MyString &&description) noexcept
    : _name(std::move(name)), _description(std::move(description)), _coordinates(Point(x, y)) {}

double Address::getDist(const Address &other) const noexcept
{
    return _coordinates.getDist(other._coordinates);
}
