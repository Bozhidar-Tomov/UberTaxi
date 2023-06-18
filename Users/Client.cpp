#include "Client.h"
#include "../System.h"
#include "../constants.h"

Client::Client(const MyString &name, const MyString &password, double moneyAvailable, System *sys)
    : User(name, password, moneyAvailable, sys) {}

Client::Client(MyString &&name, MyString &&password, double moneyAvailable, System *sys)
    : User(std::move(name), std::move(password), moneyAvailable, sys) {}

void Client::order(Address &&pickupAddress, Address &&destAddress, uint8_t passengerCount)
{
    if (_currentOrder.get())
        throw std::runtime_error("There is an active order. Cannot create another one.");

    SharedPtr<Order> newOrder(new Order(std::move(pickupAddress), std::move(destAddress), this, passengerCount));
    newOrder->changeStatus(OrderStatus::Pending);
    this->addOrder(newOrder);
    _sys->addOrder(newOrder);
    std::cout << "Successful order." << '\n';
}

// FIXME handle case when order is marked as finished
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
    else if (_currentOrder->isPending())
        std::cout << "Order (ID " << _currentOrder->getID() << ") is pending." << std::endl;
    else if (_currentOrder->isFinished())
        std::cout << "Waiting for payment to be made." << std::endl;
    else
        std::cout << "Something went wrong." << std::endl;

    std::cout << LINE_SEPARATOR << std::endl;
}

void Client::cancelOrder()
{
    if (!_currentOrder.get())
        throw std::runtime_error("There is no active order.");

    _sys->removeOrder_clientCall(_currentOrder);
    _currentOrder.reset();
}

void Client::pay()
{
    // TODO add money to driver and update statistics
    if (!_currentOrder)
        throw std::runtime_error("No current order.");

    if (_currentOrder->isInProgress())
        throw std::runtime_error("Order is still in progress. Wait for driver to mark it as finished.");

    if (_currentOrder->isPending())
        throw std::runtime_error("Order is pending. Paying in advance is not allowed.");

    if (_currentOrder->isFinished())
    {
        if (_moneyAvailable < _currentOrder->getCost())
            throw std::runtime_error("Not enough balance to make a payment!");

        _currentOrder->changeStatus(OrderStatus::Finalized);
        _moneyAvailable -= _currentOrder->getCost();
        _currentOrder->accessDriver()->addMoney(_currentOrder->getCost());
        _sys->addProfit(_currentOrder->getCost());
        _sys->releaseOrder(_currentOrder);
    }
}

void Client::rateDriver(unsigned short rating)
{
    if (!_currentOrder)
        throw std::runtime_error("No current order.");

    if (_currentOrder->isFinished())
    {
        _currentOrder->accessDriver()->addRating(rating);
        return;
    }

    throw std::runtime_error("Cannot rate driver before current order is finalized.");
}

void Client::addMoney(double amount) noexcept
{
    _moneyAvailable += amount;
}

std::ostream &operator<<(std::ostream &out, const Client &obj)
{
    return out << static_cast<const User &>(obj);
}

std::istream &operator>>(std::istream &in, Client &obj)
{
    return in >> static_cast<User &>(obj);
}

CommandType getClientCommandType(const MyString &command)
{
    if (command == "order")
        return CommandType::Order;

    if (command == "check-order")
        return CommandType::CheckOrder;

    if (command == "cancel-order")
        return CommandType::CancelOrder;

    if (command == "pay")
        return CommandType::Pay;

    if (command == "rate")
        return CommandType::Rate;

    if (command == "add-money")
        return CommandType::AddMoney;

    return CommandType::none;
}