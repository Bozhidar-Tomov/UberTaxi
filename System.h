#pragma once
#include "MyVector/MyVector.h"
#include "Users/Client.h"
#include "Users/Driver.h"
#include <sstream>

enum UserType
{
    client,
    driver,
};

class System
{

public:
    MyVector<Client> clients;
    MyVector<Driver> drivers;
    MyVector<MyString> passwordsClients;
    MyVector<MyString> passwordsDrivers;

public:
    void loadData();
    void saveData();

    User const *loginUser(const char *username, const char *password, const UserType userType);
    User const *registerClient(const char *username, const char *password, double moneyAvailable = 0);
    User const *registerDriver(const char *username, const char *password, const char *phoneNumber, const char *plateNumber, double moneyAvailable = 0);

private:
    Client parseLineClient(std::stringstream &, char *);
    Driver parseLineDriver(std::stringstream &, char *);
};