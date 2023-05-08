#include "Client.h"

Client::Client(const MyString &userName, const MyString &password, double moneyAvailable) : User(userName, password, moneyAvailable)
{
}

Client::Client(const char *userName, const char *password, double moneyAvailable) : User(userName, password, moneyAvailable)
{
}

void Client::setName(const char *name)
{
    User::setName(name);
}

void Client::setPassword(const char *password)
{
    User::setPassword(password);
}

void Client::setMoneyAvailable(double moneyAvailable)
{
    User::setMoneyAvailable(moneyAvailable);
}

std::ostream &operator<<(std::ostream &out, const Client &obj)
{
    return out << (const User &)obj;
}
