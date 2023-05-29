#include "Driver.h"
#include "../constants.h"
#include "../System.h"
#include "../PriorityQueue/PriorityQueue.h"
#include <float.h> // including DBL_MAX
#include <iostream>

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

void Driver::checkAvailableOrders()
{
    PriorityQueue<SharedPtr<Order>> pq(DBL_MAX);

    for (size_t i = 0; i < _sys->pendingOrders.size(); ++i)
    {
        pq.push(_sys->pendingOrders[i], _currAddress.getDist(_sys->pendingOrders[i].get()->getPickupAddress()));
    }

    while (!pq.empty())
    {
        std::cout << *pq.peek() << '\n';
        pq.pop();
    }
}

std::ostream &
operator<<(std::ostream &out, const Driver &obj)
{
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
