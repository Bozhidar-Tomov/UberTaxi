#include "User.h"
#include <iostream>

User::User(const MyString &userName, const MyString &password, double moneyAvailable)
    : _name(userName), _password(password), _moneyAvailable(moneyAvailable) {}

User::User(MyString &&userName, MyString &&password, double moneyAvailable)
    : _name(std::move(userName)), _password(std::move(password)), _moneyAvailable(moneyAvailable) {}

void User::setName(const MyString &name)
{
    _name = name;
}
void User::setName(MyString &&name)
{
    _name = std::move(name);
}

const MyString &User::getName() const noexcept
{
    return _name;
}

void User::setPassword(const MyString &password)
{
    _password = password;
}
void User::setPassword(MyString &&password)
{
    _password = std::move(password);
}

const MyString &User::getPassword() const noexcept
{
    return _password;
}

void User::setMoneyAvailable(double moneyAvailable) noexcept
{
    _moneyAvailable = moneyAvailable;
}

double User::getMoneyAvailable() const noexcept
{
    return _moneyAvailable;
}

void User::addOrder(Order *order)
{
    _currentOrder = order;
}

void User::removeOrder()
{
    _currentOrder = nullptr;
}

bool User::hasOrder() const noexcept
{
    return _currentOrder;
}

// FIXME: fix logic for deleting an user

// void User::deleteAccount(const MyVector<MyString> &usernames, const MyVector<MyString> &passwords, int *usersMoney)
// {
//     usernames[_idx].~MyString();
//     passwords[_idx].~MyString();
//     usersMoney[_idx] = INT_MIN;
// }

// User login(const char *username, const char *password, const MyVector<MyString> &passwords, const MyVector<MyString> &usernames, const int *usersMoney)
// {
//     size_t size = usernames.size();

//     for (size_t i = 0; i < size; ++i)
//     {
//         if (username != usernames[i])
//             continue;

//         if (password != passwords[i])
//             throw std::invalid_argument("Incorrect password.");

//         return User(username, password, usersMoney[i]);
//     }
//     throw std::invalid_argument("User not found.");
// }

std::ostream &operator<<(std::ostream &out, const User &obj)
{
    return out << obj._name << "|" << obj._password << "|" << obj._moneyAvailable;
}

std::istream &operator>>(std::istream &in, User &obj)
{
    // TODO: reading from file logic should be here.
    // as parse<user>Line
    return in >> obj._name >> obj._password >> obj._moneyAvailable;
}
