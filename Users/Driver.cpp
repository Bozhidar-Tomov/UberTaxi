#include "Driver.h"

Driver::Driver(const MyString &name, const MyString &password, double moneyAvailable,
               const Address &address, const MyString &phoneNumber, const MyString &plateNumber)
    : User(name, password, moneyAvailable),
      _currAddress(address), _phoneNumber(phoneNumber), _plateNumber(plateNumber) {}

Driver::Driver(MyString &&name, MyString &&password, double moneyAvailable,
               Address &&address, MyString &&phoneNumber, MyString &&plateNumber) noexcept
    : User(std::move(name), std::move(password), moneyAvailable),
      _currAddress(std::move(address)), _phoneNumber(std::move(phoneNumber)), _plateNumber(std::move(plateNumber)) {}

void Driver::setPhoneNumber(const char *phoneNumber)
{
    _phoneNumber = std::move(MyString(phoneNumber));
}

void Driver::setPlateNumber(const char *plateNumber)
{
    _plateNumber = std::move(MyString(plateNumber));
}

void Driver::changeCurrAddress(const Address &currAddress)
{
    _currAddress = currAddress;
}

void Driver::changeCurrAddress(Address &&currAddress) noexcept
{
    _currAddress = std::move(currAddress);
}

std::ostream &operator<<(std::ostream &out, const Driver &obj)
{
    return out << (const User &)obj << "|" << obj._phoneNumber << "|" << obj._plateNumber;
}
