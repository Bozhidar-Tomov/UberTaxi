#include "Driver.h"
#include "../constants.h"
#include "../System.h"
#include "../PriorityQueue/PriorityQueue.h"
// #include <float.h> // including DBL_MAX
#include <iostream>
#include "../Utils.h"

Driver::Driver(const MyString &name, const MyString &password, double moneyAvailable,
               const Address &address, const MyString &phoneNumber, const MyString &plateNumber, double chargePerKm)
    : User(name, password, moneyAvailable),
      _currAddress(address), _phoneNumber(phoneNumber), _plateNumber(plateNumber),
      _chargePerKm(chargePerKm) {}

Driver::Driver(MyString &&name, MyString &&password, double moneyAvailable,
               Address &&address, MyString &&phoneNumber, MyString &&plateNumber, double chargePerKm) noexcept
    : User(std::move(name), std::move(password), moneyAvailable),
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

void Driver::declineOrder(size_t orderID)
{
    for (size_t i = 0; i < _upcomingOrders.size(); ++i)
        if (_upcomingOrders[i]->getID() == orderID)
            try
            {
                _sys->notifyClosestDriver(_upcomingOrders[i], this);
                _upcomingOrders.pop_at(i);
            }
            catch (const std::runtime_error &e)
            {
                std::cout << e.what() << std::endl
                          << "Cannot cancel order because you are the only available driver who can take it."
                          << std::endl;
            }
            catch (const std::exception &e)
            {
                std::cout << "Cannot decline order. Reason: " << e.what() << std::endl;
            }
}

void Driver::finishOrder()
{
    _currentOrder->setCost(_currentOrder->getPickupAddress().getDist(_currentOrder->getDestAddress()) * _chargePerKm);
    _currAddress = _currentOrder->getDestAddress();
    _sys->finishOrder(_currentOrder);
}

std::ostream &operator<<(std::ostream &out, const Driver &obj)
{
    if (&out == &std::cout)
    {
        return out << static_cast<const User &>(obj) << std::endl
                   << "Plate Number: " << obj._plateNumber << std::endl
                   << "Phone Number: " << obj._phoneNumber;
    }
    return out << (const User &)obj << DELIM
               << obj._phoneNumber << DELIM
               << obj._plateNumber << DELIM
               << obj._chargePerKm;
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

    return in;
}
