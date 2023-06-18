#include "Order.h"
#include "../constants.h"

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
const Client *Order::getClient() const noexcept
{
  return _client;
}
Client *Order::accessClient()
{
  return _client;
}

void Order::assignDriver(Driver *driver) noexcept
{
  _driver = driver;
}

void Order::updateArriveTime(unsigned short minutes) noexcept
{
  _arriveIn = minutes;
}

void Order::changeStatus(OrderStatus status) noexcept
{
  _status = status;
}

bool Order::isPending() const noexcept
{
  return _status == OrderStatus::Pending;
}

bool Order::isInProgress() const noexcept
{
  return _status == OrderStatus::InProgress;
}

bool Order::isFinished() const noexcept
{
  return _status == OrderStatus::Finished;
}

bool Order::isFinalized() const noexcept
{
  return _status == OrderStatus::Finalized;
}

void Order::setCost(double cost) noexcept
{
  _cost = cost;
}

double Order::getCost() const noexcept
{
  return _cost;
}

std::ostream &operator<<(std::ostream &out, const Order &obj)
{
  if (&out == &std::cout)
    return out << "ID --> " << obj._id << '\n'
               << "Pickup address --> " << obj._pickupAddress << '\n'
               << "Destination --> " << obj._destAddress << '\n'
               << "Number of passengers --> " << int16_t(obj._passengerCount);

  return out << obj._id << DELIM
             << obj._pickupAddress << DELIM
             << obj._destAddress << DELIM
             << int16_t(obj._passengerCount) << DELIM
             << obj._cost;
}
