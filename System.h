#pragma once
#include "MyVector/MyVector.h"
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
    MyVector<Order> orders;

public:
    void loadData();
    void saveData();

    const Driver *getClosestDriver(const Address &) const;
    void notifyDrivers() const;

    User const *loginUser(const char *username, const char *password, const UserType userType);
    User const *registerClient(const char *username, const char *password, double moneyAvailable = 0);
    User const *registerDriver(const char *username, const char *password, const char *phoneNumber, const char *plateNumber, double moneyAvailable = 0);

private:
    Client parseLineClient(std::stringstream &, char *);
    Driver parseLineDriver(std::stringstream &, char *);
};