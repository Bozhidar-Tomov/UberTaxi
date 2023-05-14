#pragma once
#include "MyVector/MyVector.h"
#include "Users/Client.h"
#include "Users/Driver.h"
#include "Order.h"
#include <sstream>

// class Order;

enum UserType
{
    client,
    driver,
};

// TODO: make System a singleton class
class System
{

public:
    MyVector<Client> clients;
    MyVector<Driver> drivers;
    MyVector<Order> orders;

public:
    void loadData();
    void saveData();

    void addOrder(const Order &);

    User *loginUser(const char *username, const char *password, const UserType userType);
    User const *registerClient(const char *username, const char *password, double moneyAvailable = 0);
    User const *registerDriver(const char *username, const char *password, const char *phoneNumber, const char *plateNumber, double moneyAvailable = 0);

private:
    Client parseLineClient(std::stringstream &, char *);
    Driver parseLineDriver(std::stringstream &, char *);

    void removeOrder();
};