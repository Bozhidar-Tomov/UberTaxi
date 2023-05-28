#pragma once
#include "../MyString/MyString.h"
#include "../Address.h"
#include "User.h"

class Driver : public User
{
    Address _currAddress;
    MyString _phoneNumber;
    MyString _plateNumber;

public:
    Driver() = default;
    Driver(const MyString &, const MyString &, double,
           const Address &, const MyString &, const MyString &);

    Driver(MyString &&, MyString &&, double,
           Address &&, MyString &&, MyString &&) noexcept;

    void setPhoneNumber(const char *);
    void setPlateNumber(const char *);

    void changeCurrAddress(const Address &);
    void changeCurrAddress(Address &&) noexcept;

    void checkAvailableOrders();
    void acceptOrder();
    void declineOrder();
    void finishOrder();
    void acceptPayment();

    friend std::ostream &operator<<(std::ostream &, const Driver &);
};