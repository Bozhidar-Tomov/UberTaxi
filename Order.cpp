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
