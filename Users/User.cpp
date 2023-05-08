#include "User.h"
#include <iostream>

User::User(const MyString &userName, const MyString &password, double moneyAvailable, size_t idx) : _userName(userName), _password(password), _moneyAvailable(moneyAvailable), _idx(idx)
{
}

User::User(const char *userName, const char *password, double moneyAvailable, size_t idx) : _userName(userName), _password(password), _moneyAvailable(moneyAvailable), _idx(idx)
{
}

User::User(MyString &&userName, MyString &&password, double moneyAvailable) : _userName(std::move(userName)), _password(std::move(password)), _moneyAvailable(moneyAvailable)
{
}

double User::getMoneyAvailable() const noexcept
{
    return _moneyAvailable;
}

void User::deleteAccount(const MyVector<MyString> &usernames, const MyVector<MyString> &passwords, int *usersMoney)
{
    usernames[_idx].~MyString();
    passwords[_idx].~MyString();
    usersMoney[_idx] = INT_MIN;
}

User login(const char *username, const char *password, const MyVector<MyString> &passwords, const MyVector<MyString> &usernames, const int *usersMoney)
{
    size_t size = usernames.size();

    for (size_t i = 0; i < size; ++i)
    {
        if (username != usernames[i])
            continue;

        if (password != passwords[i])
            throw std::invalid_argument("Incorrect password.");

        return User(username, password, usersMoney[i], i);
    }
    throw std::invalid_argument("User not found.");
}
