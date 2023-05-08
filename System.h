#pragma once
#include "MyVector/MyVector.h"
#include "Users/Client.h"
#include "Users/Driver.h"
#include <sstream>

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

private:
    Client parseLine(std::stringstream &);
};