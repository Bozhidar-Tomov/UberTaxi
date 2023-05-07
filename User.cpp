#include "User.h"
#include "constants.h"
#include <fstream>

User::User(const MyString &userName, const MyString &password, double moneyAvailable) : _userName(userName), _password(password), _moneyAvailable(moneyAvailable)
{
}

User::User(const char *userName, const char *password, double moneyAvailable) : _userName(userName), _password(password), _moneyAvailable(moneyAvailable)
{
}

User::User(MyString &&userName, MyString &&password, double moneyAvailable) : _userName(std::move(userName)), _password(std::move(password)), _moneyAvailable(moneyAvailable)
{
}

void User::login(const char *userName, const char *password)
{
    std::ifstream file(FILE_NAME);

    if (!file.eof())
    {
    }
}
