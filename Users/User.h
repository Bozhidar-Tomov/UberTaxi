#pragma once
#include "../MyString/MyString.h"
#include "../MyVector/MyVector.h"
#include <ostream>

class Order;
class User
{
    MyString _name;
    MyString _password;
    Order *_currentOrder = nullptr;
    double _moneyAvailable = 0;

public:
    User() = default;
    User(const MyString &, const MyString &, double);
    User(const char *, const char *, double);
    User(MyString &&, MyString &&, double);

    void setName(const char *);
    const MyString &getName() const;

    void setPassword(const char *);
    const MyString &getPassword() const;

    void setMoneyAvailable(double) noexcept;
    double getMoneyAvailable() const noexcept;

    void addOrder(Order *);
    void removeOrder();
    bool hasOrder() const noexcept;
    // void logout();
    void deleteAccount(const MyVector<MyString> &, const MyVector<MyString> &, int *);

    friend std::ostream &operator<<(std::ostream &, const User &);

private:
    bool validateUsername(const char *) const;
    bool validatePassword(const char *) const;
};
