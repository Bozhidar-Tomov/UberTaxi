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
    MyVector<SharedPtr<Order>> finishedOrders;

    double profit = 0;
    size_t driversCount = 0;
    size_t clientsCount = 0;
    size_t ordersCount = 0;

public:
    void loadData();
    void saveData();

    void addOrder(SharedPtr<Order>);
    void notifyClosestDriver(SharedPtr<Order>, Driver *excludedDriver = nullptr);
    void removeOrder_clientCall(SharedPtr<Order>); // experimental

    void finishOrder(SharedPtr<Order>);
    void releaseOrder(SharedPtr<Order>);

    void addProfit(double);

    void markOrderInProgress(size_t id);

    void resetStatistics();

    SharedPtr<Client> loginClient(const char *name, const char *password);
    SharedPtr<Driver> loginDriver(const char *name, const char *password);

    SharedPtr<Client> registerClient(const char *name, const char *password, double moneyAvailable = 0);
    SharedPtr<Driver> registerDriver(const char *name, const char *password, const char *phoneNumber, const char *plateNumber, double moneyAvailable = 0, double chargePerKm = 1);

    // TODO should be private
    void saveStatistics() const;
};