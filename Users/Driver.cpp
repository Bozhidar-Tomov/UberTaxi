#include "Driver.h"
#include "../constants.h"
#include "../System.h"
#include <iostream>
#include "../Utils.h"

Driver::Driver(const MyString &name, const MyString &password, double moneyAvailable, System *sys,
               const Address &address, const MyString &phoneNumber, const MyString &plateNumber, double chargePerKm)
    : User(name, password, moneyAvailable, sys),
      _currAddress(address), _phoneNumber(phoneNumber), _plateNumber(plateNumber),
      _chargePerKm(chargePerKm) {}

Driver::Driver(MyString &&name, MyString &&password, double moneyAvailable, System *sys,
               Address &&address, MyString &&phoneNumber, MyString &&plateNumber, double chargePerKm) noexcept
    : User(std::move(name), std::move(password), moneyAvailable, sys),
      _currAddress(std::move(address)), _phoneNumber(std::move(phoneNumber)), _plateNumber(std::move(plateNumber)),
      _chargePerKm(chargePerKm) {}

void Driver::setPhoneNumber(const char *phoneNumber)
{
    _phoneNumber = std::move(MyString(phoneNumber));
}

void Driver::setPlateNumber(const char *plateNumber)
{
    _plateNumber = std::move(MyString(plateNumber));
}

void Driver::setChargePerKm(double chargePerKm)
{
    _chargePerKm = chargePerKm;
}

void Driver::changeCurrAddress(const Address &currAddress)
{
    _currAddress = currAddress;
}

void Driver::changeCurrAddress(Address &&currAddress) noexcept
{
    _currAddress = std::move(currAddress);
}

const Address &Driver::getAddress() const
{
    return _currAddress;
}

void Driver::getAvailableOrders() const
{
    if (_currentOrder)
        throw std::logic_error(
            *MyString("You have an active order (ID ")
                 .append(intToChar(_currentOrder->getID()))
                 .append(")")
                 .append("\n"));

    if (_upcomingOrders.empty())
        throw std::logic_error("No orders available right now.");

    std::cout << LINE_SEPARATOR << std::endl;
    for (size_t i = 0; i < _upcomingOrders.size(); ++i)
        std::cout << *_upcomingOrders[i] << std::endl
                  << LINE_SEPARATOR << std::endl;
}

void Driver::addOrder(SharedPtr<Order> order)
{
    _upcomingOrders.push_back(order);
}

void Driver::acceptOrder(size_t orderID, unsigned short minutes)
{
    if (_currentOrder)
        throw std::logic_error(
            *MyString("Cannot accept new order before finishing current order. Order in progress ID: ")
                 .append(intToChar(_currentOrder->getID()))
                 .append("\n"));

    for (size_t i = 0; i < _upcomingOrders.size(); ++i)
    {
        if (_upcomingOrders[i]->getID() == orderID)
        {
            _upcomingOrders[i]->assignDriver(this);
            _upcomingOrders[i]->updateArriveTime(minutes);

            _currentOrder = _upcomingOrders[i];
            _upcomingOrders.pop_at(i);

            _sys->markOrderInProgress(orderID);
            return;
        }
    }
    throw std::invalid_argument("Order not found.");
}

void Driver::declineOrder(size_t orderID)
{
    if (_currentOrder)
        throw std::runtime_error(*MyString("Cannot decline order that is in progress ID (")
                                      .append(intToChar(_currentOrder->getID()))
                                      .append(")."));

    if (_upcomingOrders.empty())
        throw std::runtime_error("No orders available at the moment.");

    for (size_t i = 0; i < _upcomingOrders.size(); ++i)
        if (_upcomingOrders[i]->getID() == orderID)
        {
            _sys->notifyClosestDriver(_upcomingOrders[i], this);
            _upcomingOrders.pop_at(i);
        }
    throw std::invalid_argument("Order not found.");
}

void Driver::finishOrder()
{
    if (!_currentOrder)
        throw std::runtime_error("No order in progress");

    _currentOrder->setCost(_currentOrder->getPickupAddress().getDist(_currentOrder->getDestAddress()) * _chargePerKm);
    _currAddress = _currentOrder->getDestAddress();
    _sys->finishOrder(_currentOrder);
}

void Driver::addRating(double rating)
{
    _rating.addRating(rating);
}

void Driver::removeOrderFromPool(size_t ID)
{
    for (size_t i = 0; i < _upcomingOrders.size(); ++i)
        if (_upcomingOrders[i]->getID() == ID)
            _upcomingOrders.pop_at(i);
}

std::ostream &operator<<(std::ostream &out, const Driver &obj)
{
    if (&out == &std::cout)
    {
        out << static_cast<const User &>(obj) << std::endl
            << "Plate Number: " << obj._plateNumber << std::endl
            << "Phone Number: " << obj._phoneNumber << std::endl
            << "Rating: ";

        if (obj._rating)
            out << obj._rating << std::endl;
        else
            out << "not rated" << std::endl;

        return out;
    }

    return out << (const User &)obj << DELIM
               << obj._phoneNumber << DELIM
               << obj._plateNumber << DELIM
               << obj._chargePerKm << DELIM
               << obj._rating;
}

std::ostream &operator<<(std::ostream &out, const Driver::Rating &obj)
{
    if (&out == &std::cout)
        return out << obj._rating;

    return out << obj._rating << DELIM << obj._count;
}

std::istream &operator>>(std::istream &in, Driver &obj)
{
    in >> static_cast<User &>(obj);
    static char buff[BUFF_SIZE];

    in.getline(buff, BUFF_SIZE, DELIM);
    obj.setPhoneNumber(buff);

    in.getline(buff, BUFF_SIZE, DELIM);
    obj.setPlateNumber(buff);

    in.getline(buff, BUFF_SIZE, DELIM);
    obj.setChargePerKm(strToDouble(buff));

    in >> obj._rating;

    return in;
}

std::istream &operator>>(std::istream &in, Driver::Rating &obj)
{
    static char buff[BUFF_SIZE];

    in.getline(buff, BUFF_SIZE, DELIM);
    obj._rating = strToDouble(buff);

    in.getline(buff, BUFF_SIZE, DELIM);
    obj._count = strToSize_t(buff);

    return in;
}

Optional<CommandType> getDriverCommandType(const MyString &command)
{
    if (command == "change-address")
        return CommandType::ChangeAddress;

    if (command == "get-messages")
        return CommandType::GetMessages;

    if (command == "get-orders")
        return CommandType::GetAvailableOrders;

    if (command == "accept-order")
        return CommandType::AcceptOrder;

    if (command == "decline-order")
        return CommandType::DeclineOrder;

    if (command == "finish-order")
        return CommandType::FinishOrder;
    if (command == "logout")
        return CommandType::Logout;

    return getUserCommandType(command);
}

void Driver::Rating::addRating(double rating)
{
    _rating = (_rating * _count + rating) / ++_count;
}

Driver::Rating::operator bool() const noexcept
{
    return _rating != 0;
}
