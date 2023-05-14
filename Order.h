#pragma once
#include "MyString/MyString.h"
// #include "Users/Client.h"
// #include "Users/Driver.h"

class Client;
class Driver;
class Order
{
    MyString _address;
    MyString _dest;

    const Client *_client = nullptr;
    const Driver *_driver = nullptr;

    double cost = 0;

public:
    Order() = default;
    Order(const char *, const char *, const Client *, const Driver *);
    Order(const MyString &, const MyString &, const Client *, const Driver *);

    void changeAddress(const char *);
};