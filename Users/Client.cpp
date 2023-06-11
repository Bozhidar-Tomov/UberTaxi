#include "Client.h"
#include "../System.h"
#include "../constants.h"

// Client::Client(const MyString &userName, const MyString &password, double moneyAvailable)
//     : User(userName, password, moneyAvailable) {}

Client::Client(MyString &&userName, MyString &&password, double moneyAvailable)
    : User(std::move(userName), std::move(password), moneyAvailable) {}

void Client::order(Address &&pickupAddress, Address &&destAddress, uint8_t passengerCount)
{
    if (_currentOrder.get())
        throw std::runtime_error("There is an active order. Cannot create another one.");

    SharedPtr<Order> newOrder(new Order(std::move(pickupAddress), std::move(destAddress), this, passengerCount));
    this->addOrder(newOrder);
    _sys->addOrder(newOrder);
}

void Client::checkOrder() const
{
    std::cout << LINE_SEPARATOR << std::endl;

    if (!_currentOrder.get())
    {
        std::cout << "No order available." << std::endl;
        return;
    }

    if (_currentOrder->isInProgress())
    {
        std::cout << "Order (ID " << _currentOrder->getID() << ") is in progress." << std::endl;
        std::cout << "Driver information:" << std::endl;
        std::cout << *_currentOrder->getDriver() << std::endl;
        std::cout << "Arrives in: " << _currentOrder->getArriveIn() << " mins." << std::endl;
    }
    else if (!_currentOrder->getDriver())
        std::cout << "Order (ID " << _currentOrder->getID() << ") is pending." << std::endl;

    std::cout << LINE_SEPARATOR << std::endl;
}

void Client::cancelOrder()
{
    if (!_currentOrder.get())
        throw std::runtime_error("There is no active order.");

    _sys->removeOrder(_currentOrder);
}

std::ostream &operator<<(std::ostream &out, const Client &obj)
{
    return out << static_cast<const User &>(obj);
}

std::istream &operator>>(std::istream &in, Client &obj)
{
    return in >> static_cast<User &>(obj);
}
