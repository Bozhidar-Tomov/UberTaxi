#include "Client.h"
#include "../System.h"

// Client::Client(const MyString &userName, const MyString &password, double moneyAvailable)
//     : User(userName, password, moneyAvailable) {}

Client::Client(MyString &&userName, MyString &&password, double moneyAvailable)
    : User(std::move(userName), std::move(password), moneyAvailable) {}

void Client::order(Address &&pickupAddress, Address &&destAddress, uint8_t passengerCount)
{
    SharedPtr<Order> newOrder(new Order(std::move(pickupAddress), std::move(destAddress), this, nullptr, passengerCount));
    this->addOrder(newOrder);
    _sys->addOrder(newOrder);
}

void Client::checkOrder()
{
    if (_currentOrder->isInProgress())
    {
        // TODO user should have multiple orders, not just one.
    }
}

std::ostream &operator<<(std::ostream &out, const Client &obj)
{
    return out << (const User &)obj;
}

std::istream &operator>>(std::istream &in, Client &obj)
{
    return in >> (User &)(obj);
}
