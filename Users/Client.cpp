#include "Client.h"
#include "../System.h"

// Client::Client(const MyString &userName, const MyString &password, double moneyAvailable)
//     : User(userName, password, moneyAvailable) {}

Client::Client(MyString &&userName, MyString &&password, double moneyAvailable)
    : User(std::move(userName), std::move(password), moneyAvailable) {}

void Client::order(Address &&pickupAddress, Address &&destAddress, uint8_t passengerCount)
{
    MyVector<Client *> cl;
    cl.push_back(this);

    SharedPtr<Order> newOrder(new Order(std::move(pickupAddress), std::move(destAddress), std::move(cl), nullptr, passengerCount));
    this->addOrder(newOrder);
    _sys->addOrder(newOrder);
}

std::ostream &operator<<(std::ostream &out, const Client &obj)
{
    return out << (const User &)obj;
}

std::istream &operator>>(std::istream &in, Client &obj)
{
    return in >> (User &)(obj);
}
