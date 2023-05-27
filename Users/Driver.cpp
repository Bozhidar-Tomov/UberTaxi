#include "Driver.h"

Driver::Driver(const MyString &name, const MyString &password, double moneyAvailable,
               const MyString &phoneNumber, const MyString &plateNumber)
    : User(name, password, moneyAvailable),
      _phoneNumber(phoneNumber), _plateNumber(plateNumber) {}

Driver::Driver(MyString &&name, MyString &&password, double moneyAvailable,
               MyString &&phoneNumber, MyString &&plateNumber) noexcept
    : User(std::move(name), std::move(password), moneyAvailable),
      _phoneNumber(std::move(phoneNumber)), _plateNumber(std::move(plateNumber)) {}

void Driver::setPhoneNumber(const char *phoneNumber)
{
    _phoneNumber = std::move(MyString(phoneNumber));
}

void Driver::setPlateNumber(const char *plateNumber)
{
    _plateNumber = std::move(MyString(plateNumber));
}

std::ostream &operator<<(std::ostream &out, const Driver &obj)
{
    return out << (const User &)obj << "|" << obj._phoneNumber << "|" << obj._plateNumber;
}
