#pragma once
#include "../MyString/MyString.h"
#include "../MyVector/MyVector.h"

class User
{
    MyString _userName;
    MyString _password;
    double _moneyAvailable = 0;

    size_t _idx = SIZE_MAX;

public:
    User() = default;
    User(const MyString &, const MyString &, double, size_t);
    User(const char *, const char *, double, size_t);
    User(MyString &&, MyString &&, double = 0);

    double getMoneyAvailable() const noexcept;
    // void logout();
    void deleteAccount(const MyVector<MyString> &, const MyVector<MyString> &, int *);
};

User login(const char *, const char *, const MyVector<MyString> &, const MyVector<MyString> &, const int *);
