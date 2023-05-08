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
