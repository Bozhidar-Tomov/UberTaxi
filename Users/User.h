#pragma once
#include "../MyString/MyString.h"
#include "../MyVector/MyVector.h"
#include <ostream>
#include <istream>

// TODO: Fix alignment of all classes
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
    User(MyString &&, MyString &&, double);

    void setName(const MyString &);
    void setName(MyString &&);
    const MyString &getName() const noexcept;

    void setPassword(const MyString &);
    void setPassword(MyString &&);
    const MyString &getPassword() const noexcept;

    void setMoneyAvailable(double) noexcept;
    double getMoneyAvailable() const noexcept;

    void addOrder(Order *);
    void removeOrder();
    bool hasOrder() const noexcept;
    // void logout();
    // void deleteAccount(const MyVector<MyString> &, const MyVector<MyString> &, int *);

    friend std::ostream &operator<<(std::ostream &, const User &);
    friend std::istream &operator>>(std::istream &, User &);

private:
    bool validateUsername(const char *) const;
    bool validatePassword(const char *) const;
};
