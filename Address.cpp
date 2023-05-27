#include "Address.h"

Address::Address(const MyString &name, double x, double y, const MyString &description)
    : _coordinates(Point(x, y)), _name(name), _description(description) {}

Address::Address(MyString &&name, double x, double y, MyString &&description) noexcept
    : _coordinates(Point(x, y)), _name(std::move(name)), _description(std::move(description)) {}

double Address::getDist(const Address &other) const
{
    return _coordinates.getDist(other._coordinates);
}
