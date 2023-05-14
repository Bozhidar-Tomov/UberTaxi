#include "Client.h"
#include "../Order.h"
#include "../System.h"

Client::Client(const MyString &userName, const MyString &password, double moneyAvailable, System *sys) : User(userName, password, moneyAvailable, sys)
{
}

Client::Client(const char *userName, const char *password, double moneyAvailable, System *sys) : User(userName, password, moneyAvailable, sys)
{
}

void Client::order(const char *address, const char *dest)
{
    // TODO: make order_error exception?
    if (_currentOrder)
        throw std::runtime_error("There is an order in progress. You cannot have multiple orders simultaneously.");

    _sys->addOrder(Order(address, dest, this, nullptr));
}

std::ostream &operator<<(std::ostream &out, const Client &obj)
{
    return out << (const User &)obj;
}
