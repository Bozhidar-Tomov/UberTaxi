#include "Driver.h"

Driver::Driver(const char *userName, const char *password, double moneyAvailable, size_t idx,
               const char *phoneNumber, const char *plateNumber) : User(userName, password, moneyAvailable, idx),
                                                                   _phoneNumber(phoneNumber), _plateNumber(plateNumber)
{
}

Driver::Driver(const MyString &userName, const MyString &password, double moneyAvailable, size_t idx,
               const MyString &phoneNumber, const MyString &plateNumber) : User(userName, password, moneyAvailable, idx),
                                                                           _phoneNumber(phoneNumber), _plateNumber(plateNumber)
{
}
