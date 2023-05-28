#include <fstream>
#include <sstream>
#include <float.h> // including DBL_MAX
#include "System.h"
#include "constants.h"
#include "Exceptions/file_stream_error.h"

namespace
{
    bool isDigit(const char ch)
    {
        return (ch >= '0' && ch <= '9');
    }

    bool isLower(const char ch)
    {
        return (ch >= 'a' && ch <= 'z');
    };

    bool isUpper(const char ch)
    {
        return (ch >= 'A' && ch <= 'Z');
    };

    bool isAlpha(const char ch)
    {
        return (isUpper(ch) || isLower(ch));
    }

    bool isSpace(const char ch)
    {
        return (ch == ' ');
    };

    bool validateUsername(const char *username)
    {
        const char *begin = username;

        if (!username || !*username || !isUpper(*username))
            return false;

        while (isAlpha(*(++username)))
            ;

        if (!isSpace(*username))
            return false;

        while (!isAlpha(*(++username)))
            ;

        if (username - begin > MAX_NAME_LEN || username - begin < MIN_NAME_LEN)
            return false;

        return true;
    }

    bool validatePassword(const char *password)
    {
        size_t idx = 0;
        bool hasDigit = false;
        bool hasUpper = false;
        bool hasLower = false;
        bool hasSymbol = false;

        if (!password)
            return false;

        do
        {
            ++idx;
            if (isdigit(*password))
                hasDigit = true;

            else if (isUpper(*password))
                hasUpper = true;

            else if (isLower(*password))
                hasLower = true;
            else
                hasSymbol = true;
        } while (*(++password));

        if (idx > MAX_PASSWORD_LEN || idx < MIN_PASSWORD_LEN)
            return false;

        return hasDigit && hasUpper && hasLower && hasSymbol;
    }
}

void System::loadData()
{
    std::ifstream file(CLIENT_DATA_FILE_DIR, std::ios::in);

    if (!file.is_open())
        throw file_stream_error("Cannot open file!", CLIENT_DATA_FILE_DIR);

    std::stringstream ss;
    char line[BUFF_SIZE];

    while (!file.eof() && file.getline(line, BUFF_SIZE))
    {
        Client c;

        ss.clear();
        ss.seekp(0, std::ios::beg);
        ss.str(line);

        ss >> c;
        clients.push_back(std::move(c));
    }

    file.close();

    file.open(DRIVER_DATA_FILE_DIR, std::ios::in);

    if (!file.is_open())
        throw file_stream_error("Cannot open file!", DRIVER_DATA_FILE_DIR);

    while (!file.eof() && file.getline(line, BUFF_SIZE))
    {
        Driver d;

        ss.clear();
        ss.seekp(0, std::ios::beg);
        ss.str(line);

        ss >> d;
        drivers.push_back(std::move(d));
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

const Driver *System::getClosestDriver(const Address &address) const
{
    double smallestDist = DBL_MAX;
    const Driver *driver = nullptr;
    static double dist;

    for (size_t i = 0; i < drivers.size(); ++i)
    {
        if (!drivers[i].hasOrder())
        {
            dist = drivers[i].getAddress().getDist(address);

            if (dist < smallestDist)
            {
                driver = &drivers[i];
                smallestDist = dist;
            }
        }
    }
    return driver;
}

// TODO: notify drivers. maybe do a pool with pending orders
void System::notifyDrivers() const
{
    // for (size_t i = 0; i < drivers.size(); ++i)
    // {
    // }
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

    drivers.push_back(std::move(Driver(MyString(name), MyString(password), moneyAvailable, Address(), MyString(phoneNumber), MyString(plateNumber))));
    return &drivers[drivers.size() - 1];
}