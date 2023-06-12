#pragma once
#include "../MyVector/MyVector.h"
#include "../Address.h"
#include "IdGenerator.h"
#include <iostream>

class Driver;
class Client;

enum class OrderStatus
{
    Pending,
    InProgress,
    Finished,
    Canceled,
    Finalized,
};

class Order
{
    // IDEA store idx as member variable
    Address _pickupAddress;
    Address _destAddress;

    Client *_client = nullptr;
    Driver *_driver = nullptr;

    size_t _id = 0;
    double _cost = 0;
    uint8_t _passengerCount = 0;

    unsigned short _arriveIn = 0;
    OrderStatus _status = OrderStatus::Pending;

public:
    Order(const Address &, const Address &,
          Client *,
          uint8_t);
    Order(Address &&, Address &&,
          Client *,
          uint8_t);
    ~Order() noexcept = default;

    const Address &getPickupAddress() const noexcept;
    const Address &getDestAddress() const noexcept;
    size_t getID() const noexcept;
    unsigned short getArriveIn() const noexcept;

    const Driver *getDriver() const noexcept;
    Driver *accessDriver();

    const Client *getClient() const noexcept;
    Client *accessClient();

    void assignDriver(Driver *) noexcept;
    void updateArriveTime(unsigned short) noexcept;

    void changeStatus(OrderStatus status) noexcept;

    bool isPending() const noexcept;
    bool isInProgress() const noexcept;
    bool isFinished() const noexcept;

    void setCost(double) noexcept;
    double getCost() const noexcept;

    friend std::ostream &operator<<(std::ostream &, const Order &);
};