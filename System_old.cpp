#include <iostream>
#include <fstream>
#include "System_old.h"
#include "constants.h"
#include "Exceptions/file_stream_error.h"
#include "Utils.h"

// TODO: improve structure of code. a lot of repeating and insufficient code
//       consider MyVector<Type*> instead of MyVector<Type> aka array of pointers instead of objects

void System::loadData()
{
    // TODO: try using/defining operator>>
    int idx = 0;
    static std::stringstream ss;
    static char line[BUFF_SIZE]{'\0'};

    std::ifstream file(CLIENT_DATA_FILE_DIR, std::ios::in);

    if (!file.is_open())
        throw file_stream_error("Cannot open file!", CLIENT_DATA_FILE_DIR);

    while (!file.eof() && file.getline(line, BUFF_SIZE))
    {
        ++idx;
        ss.clear();
        ss.seekp(0, std::ios::beg);
        ss.str(line);

        clients.push_back(std::move(parseLineClient(ss, line)));
    }

    file.close();

    file.open(DRIVER_DATA_FILE_DIR, std::ios::in);

    if (!file.is_open())
        throw file_stream_error("Cannot open file!", DRIVER_DATA_FILE_DIR);

    while (!file.eof() && file.getline(line, BUFF_SIZE))
    {
        ++idx;
        ss.clear();
        ss.seekp(0, std::ios::beg);
        ss.str(line);

        // FIXME: make sure that move semantics are called!
        drivers.push_back(std::move(parseLineDriver(ss, line)));
    }

    file.close();
}

void System::saveData()
{
    std::ofstream file(CLIENT_DATA_FILE_DIR, std::ios::out);

    if (!file.is_open())
        throw file_stream_error("Cannot open file!", CLIENT_DATA_FILE_DIR);

    for (size_t i = 0; i < clients.size(); ++i)
        file << clients[i] << '\n';

    file.close();

    file.open(DRIVER_DATA_FILE_DIR, std::ios::out);

    if (!file.is_open())
        throw file_stream_error("Cannot open file!", DRIVER_DATA_FILE_DIR);

    for (size_t i = 0; i < drivers.size(); ++i)
        file << drivers[i] << '\n';

    file.close();
}

static bool isDigit(const char ch)
{
    return (ch >= '0' && ch <= '9');
}

static bool isLower(const char ch)
{
    return (ch >= 'a' && ch <= 'z');
};

static bool isUpper(const char ch)
{
    return (ch >= 'A' && ch <= 'Z');
};

static bool isAlpha(const char ch)
{
    return (isUpper(ch) || isLower(ch));
}

static bool isSpace(const char ch)
{
    return (ch == ' ');
};

static bool validateUsername(const char *username)
{
    static const char *begin = username;

    if (!username || !*username || !isUpper(*username))
        return false;

    while (!isAlpha(*(++username)))
        ;

    if (!isSpace(*username))
        return false;

    while (!isAlpha(*(++username)))
        ;

    if (username - begin > MAX_NAME_LEN || username - begin < MIN_NAME_LEN)
        return false;

    return true;
}

static bool validatePassword(const char *password)
{
    static const char *begin = password;
    bool hasDigit = false;
    bool hasUpper = false;
    bool hasLower = false;
    bool hasSymbol = false;

    if (!password)
        return false;

    while (*(++password))
    {
        if (isdigit(*password))
            hasDigit = true;

        else if (isUpper(*password))
            hasUpper = true;

        else if (isLower(*password))
            hasLower = true;
        else
            hasSymbol = true;
    }

    if (begin - password > MAX_PASSWORD_LEN || begin - password < MIN_PASSWORD_LEN)
        return false;

    return hasDigit && hasUpper && hasLower && hasSymbol;
}

User const *System::loginUser(const char *name, const char *password, const UserType userType)
{
    if (userType == UserType::client)
    {
        for (size_t i = 0; i < clients.size(); ++i)
        {
            if (clients[i].getName() != name)
                continue;

            if (clients[i].getPassword() == password)
                return &clients[i];
        }
    }

    for (size_t i = 0; i < drivers.size(); ++i)
    {
        if (drivers[i].getName() != name)
            continue;

        if (drivers[i].getPassword() == password)
            return &drivers[i];
    }
    return nullptr;
}

User const *System::registerClient(const char *name, const char *password, double moneyAvailable)
{
    for (size_t i = 0; i < clients.size(); ++i)
        if (clients[i].getName() == name)
            return nullptr;

    if (!validateUsername(name) || !validatePassword(password))
        return nullptr;

    clients.push_back(std::move(Client(MyString(name), MyString(password), moneyAvailable)));
    return &clients[clients.size() - 1];
}

User const *System::registerDriver(const char *name, const char *password, const char *phoneNumber, const char *plateNumber, double moneyAvailable)
{
    for (size_t i = 0; i < drivers.size(); ++i)
        if (drivers[i].getName() == name)
            return nullptr;

    if (!validateUsername(name) || !validatePassword(password))
        return nullptr;

    // drivers.push_back(std::move(Driver(MyString(name), MyString(password), moneyAvailable, MyString(phoneNumber), MyString(plateNumber))));
    return &drivers[drivers.size() - 1];
}

Client System::parseLineClient(std::stringstream &stream, char *line)
{
    Client client;

    stream.getline(line, BUFF_SIZE, DELIM);
    client.setName(MyString(line));

    stream.getline(line, BUFF_SIZE, DELIM);
    client.setPassword(MyString(line));

    stream.getline(line, BUFF_SIZE, DELIM);
    client.setMoneyAvailable(strToDouble(line));

    return client;
}

Driver System::parseLineDriver(std::stringstream &stream, char *line)
{
    Driver driver;

    stream.getline(line, BUFF_SIZE, DELIM);
    driver.setName(MyString(line));

    stream.getline(line, BUFF_SIZE, DELIM);
    driver.setPassword(MyString(line));

    stream.getline(line, BUFF_SIZE, DELIM);
    driver.setMoneyAvailable(strToDouble(line));

    stream.getline(line, BUFF_SIZE, DELIM);
    driver.setPhoneNumber(line);

    stream.getline(line, BUFF_SIZE, DELIM);
    driver.setPlateNumber(line);

    return driver;
}
