#pragma once
#include "MyString/MyString.h"

class User
{
    MyString _userName;
    MyString _password;

    double _moneyAvailable = 0;

public:
    User(const MyString &, const MyString &, double = 0);
    User(const char *, const char *, double = 0);
    User(MyString &&, MyString &&, double = 0);

    void login(const char *, const char *);
    void logout();
    void deleteAccount();
    void getMoneyAvailable() const noexcept;
};