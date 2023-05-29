#include <iostream>
#include "User.h"
#include "../constants.h"
#include "../Utils.h"

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

void User::addOrder(SharedPtr<Order> order)
{
    _currentOrder = order;
}

void User::loadSystemPtr(System *sys) noexcept
{
    _sys = sys;
}

void User::removeOrder()
{
    _currentOrder.reset();
}

bool User::hasOrder() const noexcept
{
    return _currentOrder.operator bool();
}

std::ostream &operator<<(std::ostream &out, const User &obj)
{
    return out << obj._name << DELIM << obj._password << DELIM << obj._moneyAvailable;
}

std::istream &operator>>(std::istream &in, User &obj)
{
    char buff[BUFF_SIZE];

    in.getline(buff, BUFF_SIZE, DELIM);
    obj.setName(MyString(buff));

    in.getline(buff, BUFF_SIZE, DELIM);
    obj.setPassword(MyString(buff));

    in.getline(buff, BUFF_SIZE, DELIM);
    obj.setMoneyAvailable(strToDouble(buff));

    return in;
}
