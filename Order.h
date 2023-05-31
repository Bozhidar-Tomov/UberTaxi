#pragma once
#include "MyVector/MyVector.h"
#include "./Address.h"
#include "IdGenerator.h"
#include <ostream>

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

    unsigned short _arriveIn = 0;

public:
    Order(const Address &, const Address &,
          const MyVector<Client *> &, Driver *,
          uint8_t);
    Order(Address &&, Address &&,
          MyVector<Client *> &&, Driver *,
          uint8_t);
    ~Order() noexcept = default;

    const Address &getPickupAddress() const noexcept;
    const Address &getDestAddress() const noexcept;
    size_t getID() const noexcept;
    unsigned short getArriveIn() const noexcept;

    void assignDriver(Driver *) noexcept;
    void updateArriveTime(unsigned short) noexcept;

    bool isInProgress() const noexcept;

    friend std::ostream &operator<<(std::ostream &, const Order &);
};