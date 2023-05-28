#pragma once
#include "MyVector/MyVector.h"
#include "./Address.h"
#include "IdGenerator.h"

class Driver;
class Client;

class Order
{
    Address _pickupAddress;
    Address _destAddress;

    MyVector<Client *> _clients;
    Driver *_driver;

    size_t _id = 0;
    double _cost = 0;
    uint8_t _passengerCount = 0;

public:
    Order(const Address &, const Address &,
          const MyVector<Client *> &, Driver *,
          uint8_t);
    Order(Address &&, Address &&,
          MyVector<Client *> &&, Driver *,
          uint8_t);
    ~Order() noexcept = default;
};