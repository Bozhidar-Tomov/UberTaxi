#pragma once
#include "MyVector/MyVector.h"
#include "SmartPointers/SharedPtr.hxx"
#include "SmartPointers/UniquePtr.hxx"
#include "Users/Client.h"
#include "Users/Driver.h"
#include "Order/Order.h"

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

    System();

public:
    static System &getInstance();

    void loadData();
    void saveData();

    void addOrder(SharedPtr<Order>);
    void notifyClosestDriver(SharedPtr<Order>, Driver *excludedDriver = nullptr);
    void removeOrder_clientCall(SharedPtr<Order>); // experimental

    void finishOrder(SharedPtr<Order>);
    void releaseOrder(SharedPtr<Order>);

    void addProfit(double);

    void markOrderInProgress(size_t id);

    SharedPtr<Client> loginClient(const MyString &name, const MyString &password);
    SharedPtr<Driver> loginDriver(const MyString &name, const MyString &password);

    SharedPtr<Client> registerClient(MyString &&name, MyString &&password, double moneyAvailable = 0);
    SharedPtr<Driver> registerDriver(MyString &&name, MyString &&password, MyString &&phoneNumber, MyString &&plateNumber, double moneyAvailable = 0, double chargePerKm = 1);

private:
    void saveStatistics() const;
    void resetStatistics();
};