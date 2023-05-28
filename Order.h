#pragma once
#include "Users/Client.h"
#include "Users/Driver.h"
#include "MyVector/MyVector.h"
#include "./Address.h"

class Order
{
    Address _pickupAddress;
    Address _destAddress;

    MyVector<Client const *> _clients;
    Driver const *_driver;

    size_t _id = 0;
    double _cost = 0;
    uint8_t _passengerCount = 0;

public:
    Order(const Address &, const Address &,
          const MyVector<Client const *> &, Driver const *,
          size_t, double, uint8_t);
    Order(Address &&, Address &&,
          MyVector<Client const *> &&, Driver const *,
          size_t, double, uint8_t);
    ~Order() noexcept = default;
};