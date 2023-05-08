#include "Client.h"

Client::Client(const MyString &userName, const MyString &password, double moneyAvailable, size_t idx) : User(userName, password, moneyAvailable, idx)
{
}

Client::Client(const char *userName, const char *password, double moneyAvailable, size_t idx) : User(userName, password, moneyAvailable, idx)
{
}
