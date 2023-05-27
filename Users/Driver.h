#pragma once
#include "../MyString/MyString.h"
#include "User.h"

class Driver : public User
{
    MyString _phoneNumber;
    MyString _plateNumber;

public:
    Driver() = default;
    Driver(const MyString &, const MyString &, double,
           const MyString &, const MyString &);

    Driver(MyString &&, MyString &&, double,
           MyString &&, MyString &&) noexcept;

    void setPhoneNumber(const char *);
    void setPlateNumber(const char *);

    void changeAddress();
    void checkAvailableOrders();
    void acceptOrder();
    void declineOrder();
    void finishOrder();
    void acceptPayment();

    friend std::ostream &operator<<(std::ostream &, const Driver &);
};