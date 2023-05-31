#pragma once
#include "../MyString/MyString.h"
#include "../Address.h"
#include "User.h"

class Driver : public User
{
    Address _currAddress;
    MyString _phoneNumber;
    MyString _plateNumber;
    Order *_upcomingOrder = nullptr;

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

    const Address &getAddress() const;

    void checkAvailableOrders() const;
    void acceptOrder(size_t, unsigned short);
    void finishOrder();
    void acceptPayment();

    friend std::ostream &operator<<(std::ostream &, const Driver &);
    friend std::istream &operator>>(std::istream &, Driver &);
};