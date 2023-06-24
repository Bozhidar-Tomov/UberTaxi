#pragma once
#include "User.h"
#include "../MyString/MyString.h"
#include "../Address.h"

class Driver : public User
{
    struct Rating
    {
        double _rating = 0;
        size_t _count = 0;

        void addRating(double);
    };

    Address _currAddress;
    MyString _phoneNumber;
    MyString _plateNumber;
    MyVector<SharedPtr<Order>> _upcomingOrders;
    Rating _rating;

    double _chargePerKm = 1;

public:
    Driver() = default;

    Driver(const MyString &, const MyString &, double, System *,
           const Address &, const MyString &, const MyString &, double);

    Driver(MyString &&, MyString &&, double, System *,
           Address &&, MyString &&, MyString &&, double) noexcept;

    void setPhoneNumber(const char *);
    void setPlateNumber(const char *);
    void setChargePerKm(double);

    void changeCurrAddress(const Address &);
    void changeCurrAddress(Address &&) noexcept;

    const Address &getAddress() const;

    void getAvailableOrders() const;
    void addOrder(SharedPtr<Order>);
    void acceptOrder(size_t, unsigned short);
    void declineOrder(size_t);
    void finishOrder();
    void addRating(double);

    void removeOrderFromPool(size_t);

    friend std::ostream &operator<<(std::ostream &, const Driver &);
    friend std::ostream &operator<<(std::ostream &, const Driver::Rating &);

    friend std::istream &operator>>(std::istream &, Driver &);
    friend std::istream &operator>>(std::istream &, Driver::Rating &);
};
CommandType getDriverCommandType(const MyString &command);