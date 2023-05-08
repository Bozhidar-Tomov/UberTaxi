#pragma once
#include "../MyString/MyString.h"
#include "User.h"

class Client : private User
{

public:
    Client() = default;
    Client(const MyString &, const MyString &, double, size_t);
    Client(const char *, const char *, double, size_t);

    void order();
    void checkOrder();
    void cancelOrder();
    void payOrder();
    void reteDriver();
    void addMoney();
};