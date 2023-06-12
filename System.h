#pragma once
#include "MyVector/MyVector.h"
#include "SmartPointers/SharedPtr.hxx"
#include "SmartPointers/UniquePtr.hxx"
#include "Users/Client.h"
#include "Users/Driver.h"
#include "Order/Order.h"

enum UserType
{
    client,
    driver,
};

// TODO: Make it singleton
class System
{
    // IDEA: make heterogeneous container
    // IDEA: make vector of objects
    MyVector<SharedPtr<Client>> clients;
    MyVector<SharedPtr<Driver>> drivers;

    // IDEA: leave it as pointers since a lot of change is happening
    MyVector<SharedPtr<Order>> pendingOrders;
    MyVector<SharedPtr<Order>> inProgressOrders;

public:
    void loadData();
    void saveData();

    void addOrder(SharedPtr<Order>);
    void notifyClosestDriver(SharedPtr<Order>, Driver *excludedDriver = nullptr);
    void removeOrder(SharedPtr<Order>);

    void markOrderInProgress(size_t id);

    SharedPtr<Client> loginClient(const char *username, const char *password);
    SharedPtr<Driver> loginDriver(const char *username, const char *password);

    SharedPtr<Client> registerClient(const char *username, const char *password, double moneyAvailable = 0);
    SharedPtr<Driver> registerDriver(const char *username, const char *password, const char *phoneNumber, const char *plateNumber, double moneyAvailable = 0);
};