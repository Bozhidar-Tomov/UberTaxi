#include "Client.h"

Client::Client(const MyString &userName, const MyString &password, double moneyAvailable)
    : User(userName, password, moneyAvailable) {}

Client::Client(MyString &&userName, MyString &&password, double moneyAvailable)
    : User(std::move(userName), std::move(password), moneyAvailable) {}

std::ostream &operator<<(std::ostream &out, const Client &obj)
{
    return out << (const User &)obj;
}
