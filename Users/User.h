#pragma once
#include "../MyString/MyString.h"
#include "../MyVector/MyVector.h"
#include <ostream>

class Order;
class User
{
    MyString _name;
    MyString _password;
    Order const *_currentOrder = nullptr;
    double _moneyAvailable = 0;

public:
    User() = default;
    User(const MyString &, const MyString &, double);
    User(const char *, const char *, double);
    User(MyString &&, MyString &&, double);

    void setName(const char *);
    void setPassword(const char *);
    void setMoneyAvailable(double) noexcept;

    double getMoneyAvailable() const noexcept;
    void addOrder(Order const *);
    void removeOrder();
    bool hasOrder() const;
    // void logout();
    void deleteAccount(const MyVector<MyString> &, const MyVector<MyString> &, int *);

    friend std::ostream &operator<<(std::ostream &, const User &);
};

User login(const char *, const char *, const MyVector<MyString> &, const MyVector<MyString> &, const int *);
