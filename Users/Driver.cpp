#include "Driver.h"

Driver::Driver(const char *userName, const char *password, double moneyAvailable,
               const char *phoneNumber, const char *plateNumber) : User(userName, password, moneyAvailable),
                                                                   _phoneNumber(phoneNumber), _plateNumber(plateNumber)
{
}

Driver::Driver(const MyString &userName, const MyString &password, double moneyAvailable,
               const MyString &phoneNumber, const MyString &plateNumber) : User(userName, password, moneyAvailable),
                                                                           _phoneNumber(phoneNumber), _plateNumber(plateNumber)
{
}

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
