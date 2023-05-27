#include "Order.h"

Order::Order(Address &address, const Address &dest, Client const &client, Driver const &driver, double cost, uint8_t passengerCount)
    : _address(address), _dest(dest),
      _client(client), _driver(driver),
      _cost(cost), _passengerCount(passengerCount) {}

Order::Order(Address &&address, Address &&dest, Client const &client, Driver const &driver, double cost, uint8_t passengerCount)
    : _address(std::move(address)), _dest(std::move(dest)),
      _client(client), _driver(driver),
      _cost(cost), _passengerCount(passengerCount) {}

void Order::changeAddress(const Address &newAddress)
{
    _address = newAddress;
}
void Order::changeAddress(Address &&newAddress) noexcept
{
    _address = std::move(newAddress);
}
