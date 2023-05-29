#pragma once
#include "MyVector/MyVector.h"
#include "SmartPointers/SharedPtr.hxx"
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
    MyVector<Client> clients;
    MyVector<Driver> drivers;
    MyVector<SharedPtr<Order>> orders;

public:
    void loadData();
    void saveData();

    const Driver *getClosestDriver(const Address &) const;
    void notifyDrivers() const;

    User *loginUser(const char *username, const char *password, const UserType userType);
    User *registerClient(const char *username, const char *password, double moneyAvailable = 0);
    User *registerDriver(const char *username, const char *password, const char *phoneNumber, const char *plateNumber, double moneyAvailable = 0);
};