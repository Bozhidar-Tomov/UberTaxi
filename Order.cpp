#include "Order.h"

Order::Order(const Address &address, const Address &dest,
             const MyVector<Client const *> &clients, Driver const *driver,
             size_t id, double cost, uint8_t passengerCount)
    : _pickupAddress(address), _destAddress(dest),
      _clients(clients), _driver(driver),
      _id(id), _cost(cost), _passengerCount(passengerCount) {}

Order::Order(Address &&address, Address &&dest,
             MyVector<Client const *> &&clients, Driver const *driver,
             size_t id, double cost, uint8_t passengerCount)
    : _pickupAddress(std::move(address)), _destAddress(std::move(dest)),
      _clients(std::move(clients)), _driver(driver),
      _id(id), _cost(cost), _passengerCount(passengerCount) {}
