#pragma once
#include "MyVector/MyVector.h"
#include "SmartPointers/SharedPtr.hxx"
#include "SmartPointers/UniquePtr.hxx"
#include "Users/Client.h"
#include "Users/Driver.h"
#include "Order.h"

enum UserType
{
    client,
    driver,
};

// TODO: Make it singleton
class System
{
    // TODO: should be private
public:
    MyVector<SharedPtr<Client>> clients;
    MyVector<SharedPtr<Driver>> drivers;
    MyVector<SharedPtr<Order>> pendingOrders;
    MyVector<SharedPtr<Order>> inProgressOrders;

public:
    // TODO: add system pointer to each client and driver
    void loadData();
    void saveData();

    void addOrder(SharedPtr<Order>);
    void markOrderInProgress(SharedPtr<Order>, size_t idx);

    SharedPtr<Client> loginClient(const char *username, const char *password);
    SharedPtr<Driver> loginDriver(const char *username, const char *password);

    SharedPtr<Client> registerClient(const char *username, const char *password, double moneyAvailable = 0);
    SharedPtr<Driver> registerDriver(const char *username, const char *password, const char *phoneNumber, const char *plateNumber, double moneyAvailable = 0);
};