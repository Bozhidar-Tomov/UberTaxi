#pragma once
#include "../MyString/MyString.h"
#include "User.h"

class Client : public User
{

public:
    Client() = default;
    Client(const MyString &, const MyString &, double, System *);
    Client(const char *, const char *, double, System *);

    void order(const char *address, const char *dest);
    void checkOrder();
    void cancelOrder();
    void payOrder();
    void reteDriver();
    void addMoney();

    friend std::ostream &operator<<(std::ostream &, const Client &);
};