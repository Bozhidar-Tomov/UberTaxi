#include "User.h"
#include <iostream>

User::User(const MyString &userName, const MyString &password, double moneyAvailable, System *sys) : _name(userName), _password(password), _moneyAvailable(moneyAvailable), _sys(sys)
{
}

User::User(const char *userName, const char *password, double moneyAvailable, System *sys) : _name(userName), _password(password), _moneyAvailable(moneyAvailable), _sys(sys)
{
}

User::User(MyString &&userName, MyString &&password, double moneyAvailable) : _name(std::move(userName)), _password(std::move(password)), _moneyAvailable(moneyAvailable)
{
}

void User::setName(const char *name)
{
    _name.reset_data();
    _name.append(name);
}
const MyString &User::getName() const
{
    return _name;
}
void User::setPassword(const char *password)
{
    _password.reset_data();
    _password.append(password);
}

const MyString &User::getPassword() const
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

void User::addOrder(Order const *order)
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

std::ostream &operator<<(std::ostream &out, const User &obj)
{
    return out << obj._name << "|" << obj._password << "|" << obj._moneyAvailable;
}
