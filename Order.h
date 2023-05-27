#pragma once
#include "Users/Client.h"
#include "Users/Driver.h"
#include "./Address.h"

class Order
{
    Address _address;
    Address _dest;

    Client const &_client;
    Driver const &_driver;

    double _cost = 0;
    uint8_t _passengerCount = 0;

public:
    Order(Address &, const Address &, Client const &, Driver const &, double, uint8_t);
    Order(Address &&, Address &&, Client const &, Driver const &, double, uint8_t);
    ~Order() noexcept = default;

    void changeAddress(const Address &);
    void changeAddress(Address &&) noexcept;
};