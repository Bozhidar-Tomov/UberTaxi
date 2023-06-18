#pragma once
#include <iostream>
#include "../MyString/MyString.h"
#include "../MyVector/MyVector.h"
#include "../Order/Order.h"
#include "../SmartPointers/SharedPtr.hxx"
#include "../constants.h"
class System;

class User
{
    struct Messages
    {
    private:
        MyString _messages[MESSAGE_COUNT];
        unsigned short count = 0;
        unsigned int endPtr = 0;

    public:
        bool empty() const noexcept;
        void addMessage(MyString &&) noexcept;
        void printMessages() const noexcept;
    };

protected:
    MyString _name;
    MyString _password;
    Messages _messages;
    SharedPtr<Order> _currentOrder;
    System *_sys = nullptr;
    double _moneyAvailable = 0;

public:
    User() = default;
    User(const MyString &, const MyString &, double, System *);
    User(MyString &&, MyString &&, double, System *);

    void setName(const MyString &);
    void setName(MyString &&);
    const MyString &getName() const noexcept;

    void setPassword(const MyString &);
    void setPassword(MyString &&);
    const MyString &getPassword() const noexcept;

    void setMoneyAvailable(double) noexcept;
    double getMoneyAvailable() const noexcept;
    double addMoney(double) noexcept;

    void loadSystemPtr(System *) noexcept;

    void addOrder(SharedPtr<Order>);
    void removeOrder();
    bool hasOrder() const noexcept;

    void addMessage(MyString &&) noexcept;
    void getMessages() const;
    // void logout();
    // void deleteAccount(const MyVector<MyString> &, const MyVector<MyString> &, int *);

    friend std::ostream &operator<<(std::ostream &, const User &);
    friend std::istream &operator>>(std::istream &, User &);
};
