#include "User.h"
#include "../constants.h"
#include "../Utils.h"

User::User(const MyString &name, const MyString &password, double moneyAvailable, System *sys)
    : _name(name), _password(password), _moneyAvailable(moneyAvailable), _sys(sys) {}

User::User(MyString &&name, MyString &&password, double moneyAvailable, System *sys)
    : _name(std::move(name)), _password(std::move(password)), _moneyAvailable(moneyAvailable), _sys(sys) {}

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

double User::addMoney(double amount) noexcept
{
    return _moneyAvailable += amount;
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

void User::addMessage(MyString &&message) noexcept
{
    _messages.addMessage(std::move(message));
}

void User::getMessages() const noexcept
{
    _messages.printMessages();
}

std::ostream &
operator<<(std::ostream &out, const User &obj)
{
    if (&out == &std::cout)
        return out << "Name: " << obj._name;

    return out << obj._name << DELIM
               << obj._password << DELIM
               << obj._moneyAvailable;
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

void User::Messages::addMessage(MyString &&message) noexcept
{
    if (count != MESSAGE_COUNT)
        ++count;

    _messages[endPtr] = std::move(message);
    endPtr = (++endPtr) % MESSAGE_COUNT;
}

void User::Messages::printMessages() const noexcept
{
    unsigned short start = endPtr >= count ? endPtr - count : MESSAGE_COUNT - (count - endPtr);
    for (unsigned short i = 0; i < count; ++i)
        std::cout << _messages[(start + i) % MESSAGE_COUNT] << std::endl;
}
