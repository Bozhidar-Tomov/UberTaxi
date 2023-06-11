#include "Driver.h"
#include "../constants.h"
#include "../System.h"
#include "../PriorityQueue/PriorityQueue.h"
// #include <float.h> // including DBL_MAX
#include <iostream>
#include "../Utils.h"

Driver::Driver(const MyString &name, const MyString &password, double moneyAvailable,
               const Address &address, const MyString &phoneNumber, const MyString &plateNumber)
    : User(name, password, moneyAvailable),
      _currAddress(address), _phoneNumber(phoneNumber), _plateNumber(plateNumber) {}

Driver::Driver(MyString &&name, MyString &&password, double moneyAvailable,
               Address &&address, MyString &&phoneNumber, MyString &&plateNumber) noexcept
    : User(std::move(name), std::move(password), moneyAvailable),
      _currAddress(std::move(address)), _phoneNumber(std::move(phoneNumber)), _plateNumber(std::move(plateNumber)) {}

void Driver::setPhoneNumber(const char *phoneNumber)
{
    _phoneNumber = std::move(MyString(phoneNumber));
}

void Driver::setPlateNumber(const char *plateNumber)
{
    _plateNumber = std::move(MyString(plateNumber));
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

void Driver::checkAvailableOrders() const
{
    for (size_t i = 0; i < _upcomingOrders.size(); ++i)
        std::cout << *_upcomingOrders[i] << std::endl
                  << LINE_SEPARATOR << std::endl;
}

void Driver::addOrder(SharedPtr<Order> order)
{
    _upcomingOrders.push_back(order);
}

// TODO: update it
void Driver::acceptOrder(size_t id, unsigned short minutes)
{
    if (_currentOrder.get())
        throw std::logic_error(
            *MyString("Cannot accept new order before finishing current order. Order in progress ID: ")
                 .append(intToChar(_currentOrder->getID()))
                 .append("\n"));

    for (size_t i = 0; i < _upcomingOrders.size(); ++i)
    {
        if (_upcomingOrders[i]->getID() == id)
        {
            _upcomingOrders[i]->assignDriver(this);
            _upcomingOrders[i]->updateArriveTime(minutes);

            _currentOrder = _upcomingOrders[i];
            _upcomingOrders.pop_at(i);

            _sys->markOrderInProgress(id);
            return;
        }
    }
    throw std::invalid_argument("Order not found.");
}

std::ostream &operator<<(std::ostream &out, const Driver &obj)
{
    if (&out == &std::cout)
    {
        // TODO explicit casing
        return out << (User &)(obj) << std::endl
                   << "Plate Number: " << obj._plateNumber << std::endl
                   << "Phone Number: " << obj._phoneNumber;
    }
    return out << (const User &)obj << DELIM << obj._phoneNumber << DELIM << obj._plateNumber;
}

std::istream &operator>>(std::istream &in, Driver &obj)
{
    in >> (User &)(obj);
    char buff[BUFF_SIZE];

    in.getline(buff, BUFF_SIZE, DELIM);
    obj.setPhoneNumber(buff);

    in.getline(buff, BUFF_SIZE, DELIM);
    obj.setPlateNumber(buff);

    return in;
}
