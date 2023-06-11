#include "Order.h"

Order::Order(const Address &address, const Address &dest,
             Client *client,
             uint8_t passengerCount)
    : _pickupAddress(address), _destAddress(dest),
      _client(client),
      _passengerCount(passengerCount), _id(IdGenerator::getId()) {}

Order::Order(Address &&address, Address &&dest,
             Client *client,
             uint8_t passengerCount)
    : _pickupAddress(std::move(address)), _destAddress(std::move(dest)),
      _client(client),
      _passengerCount(passengerCount), _id(IdGenerator::getId()) {}

const Address &Order::getPickupAddress() const noexcept
{
  return _pickupAddress;
}

const Address &Order::getDestAddress() const noexcept
{
  return _destAddress;
}

size_t Order::getID() const noexcept
{
  return _id;
}

unsigned short Order::getArriveIn() const noexcept
{
  return _arriveIn;
}

const Driver *Order::getDriver() const noexcept
{
  return _driver;
}
Driver *Order::accessDriver()
{
  return _driver;
}

void Order::assignDriver(Driver *driver) noexcept
{
  _driver = driver;
}

void Order::updateArriveTime(unsigned short minutes) noexcept
{
  _arriveIn = minutes;
}

bool Order::isInProgress() const noexcept
{
  return (bool)_driver;
}

std::ostream &operator<<(std::ostream &out, const Order &obj)
{
  return out << "ID --> " << obj._id << '\n'
             << "Pickup address --> " << obj._pickupAddress << '\n'
             << "Destination --> " << obj._destAddress << '\n'
             << "Number of passengers --> " << int16_t(obj._passengerCount);
}
