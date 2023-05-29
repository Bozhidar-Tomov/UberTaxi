#pragma once
#include <ostream>
#include <istream>
#include "../MyString/MyString.h"
#include "../MyVector/MyVector.h"
#include "../Order.h"
#include "../SmartPointers/SharedPtr.hxx"

class System;
// TODO: Fix alignment of all classes
class User
{
protected:
    MyString _name;
    MyString _password;
    SharedPtr<Order> _currentOrder;
    System *_sys;
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

    void loadSystemPtr(System *) noexcept;

    void addOrder(SharedPtr<Order>);
    void removeOrder();
    bool hasOrder() const noexcept;
    // void logout();
    // void deleteAccount(const MyVector<MyString> &, const MyVector<MyString> &, int *);

    friend std::ostream &operator<<(std::ostream &, const User &);
    friend std::istream &operator>>(std::istream &, User &);
};
