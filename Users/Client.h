#pragma once
#include "../MyString/MyString.h"
#include "User.h"

class Client : private User
{

public:
    Client() = default;
    Client(const MyString &, const MyString &, double);
    Client(const char *, const char *, double);

    void setName(const char *);
    void setPassword(const char *);
    void setMoneyAvailable(double);
    void order();
    void checkOrder();
    void cancelOrder();
    void payOrder();
    void reteDriver();
    void addMoney();

    friend std::ostream &operator<<(std::ostream &, const Client &);
};