#include "Order.h"

Order::Order(const Address &address, const Address &dest,
             const MyVector<Client *> &clients, Driver *driver,
             uint8_t passengerCount)
    : _pickupAddress(address), _destAddress(dest),
      _clients(clients), _driver(driver),
      _passengerCount(passengerCount), _id(IdGenerator::getId()) {}

Order::Order(Address &&address, Address &&dest,
             MyVector<Client *> &&clients, Driver *driver,
             uint8_t passengerCount)
    : _pickupAddress(std::move(address)), _destAddress(std::move(dest)),
      _clients(std::move(clients)), _driver(driver),
      _passengerCount(passengerCount), _id(IdGenerator::getId()) {}

const Address &Order::getPickupAddress() const noexcept
{
  return _pickupAddress;
}

const Address &Order::getDestAddress() const noexcept
{
  return _destAddress;
}

const size_t Order::getID() const noexcept
{
  return _id;
}

void Order::assignDriver(Driver *driver) noexcept
{
  _driver = driver;
}

void Order::updateArriveTime(unsigned short minutes) noexcept
{
  _arriveIn = minutes;
}

std::ostream &operator<<(std::ostream &out, const Order &obj)
{
  return out << "ID --> " << obj._id << '\n'
             << "Pickup address --> " << obj._pickupAddress << '\n'
             << "Destination --> " << obj._destAddress << '\n'
             << "Number of passengers --> " << int16_t(obj._passengerCount);
}
