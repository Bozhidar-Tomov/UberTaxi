#pragma once
#include "MyString/MyString.h"
#include "VectorString/VectorString.h"

class User
{
    MyString _userName;
    MyString _password;
    double _moneyAvailable = 0;

    size_t _idx = SIZE_MAX;

public:
    User(const MyString &, const MyString &, double, size_t);
    User(const char *, const char *, double, size_t);
    User(MyString &&, MyString &&, double = 0);

    double getMoneyAvailable() const noexcept;
    // void logout();
    void deleteAccount(const VectorString &, const VectorString &, int *);
};

User login(const char *, const char *, const VectorString &, const VectorString &, const int *);
