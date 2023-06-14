#pragma once
#include "../MyString/MyString.h"
#include "User.h"
#include "../Address.h"

class Client : public User
{

public:
    Client() = default;
    Client(const MyString &, const MyString &, double, System *sys);
    Client(MyString &&, MyString &&, double, System *sys);

    void order(Address &&, Address &&, uint8_t);
    void checkOrder() const;
    void cancelOrder();
    void pay();
    void rateDriver(unsigned short);
    void addMoney(double) noexcept;

    friend std::ostream &operator<<(std::ostream &, const Client &);
    friend std::istream &operator>>(std::istream &, Client &);
};