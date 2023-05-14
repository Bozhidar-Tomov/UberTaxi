#pragma once
#include "../MyString/MyString.h"
#include "../MyVector/MyVector.h"
#include <ostream>

class Order;
class System;
class User
{
protected:
    MyString _name;
    MyString _password;
    Order const *_currentOrder = nullptr;
    double _moneyAvailable = 0;

    System *_sys = nullptr;

public:
    User() = default;
    User(const MyString &, const MyString &, double, System *);
    User(const char *, const char *, double, System *);
    User(MyString &&, MyString &&, double);

    void setName(const char *);
    const MyString &getName() const;

    void setPassword(const char *);
    const MyString &getPassword() const;

    void setMoneyAvailable(double) noexcept;
    double getMoneyAvailable() const noexcept;

    void addOrder(Order const *);
    void removeOrder();
    bool hasOrder() const noexcept;

    friend std::ostream &operator<<(std::ostream &, const User &);
};
