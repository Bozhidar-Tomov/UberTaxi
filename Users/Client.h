#pragma once
#include "../MyString/MyString.h"
#include "User.h"
#include "../Address.h"

class Client : public User
{

public:
    Client() = default;
    // Client(const MyString &, const MyString &, double);
    Client(MyString &&, MyString &&, double);

    void order(Address &&, Address &&, uint8_t);
    void checkOrder() const;
    void cancelOrder();
    void payOrder();
    void reteDriver();
    void addMoney();

    friend std::ostream &operator<<(std::ostream &, const Client &);
    friend std::istream &operator>>(std::istream &, Client &);
};