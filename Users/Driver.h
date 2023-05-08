#pragma once
#include "../MyString/MyString.h"
#include "User.h"

class Driver : private User
{
    MyString _phoneNumber;
    MyString _plateNumber;

public:
    Driver() = default;
    Driver(const char *, const char *, double, size_t,
           const char *, const char *);
    Driver(const MyString &, const MyString &, double, size_t,
           const MyString &, const MyString &);

    void changeAddress();
    void checkAvailableOrders();
    void acceptOrder();
    void declineOrder();
    void finishOrder();
    void acceptPayment();
};