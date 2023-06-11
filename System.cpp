#include <fstream>
#include <sstream>
#include <float.h> // including DBL_MAX
#include "System.h"
#include "constants.h"
#include "Exceptions/file_stream_error.h"
#include "Utils.h"

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

    size_t binarySearch(MyVector<SharedPtr<Order>> &orders, size_t id)
    {
        size_t low = 0;
        size_t high = orders.size() - 1;

        while (low <= high)
        {
            size_t mid = low + (high - low) / 2;

            if (orders[mid]->getID() == id)
                return mid;

            if (orders[mid]->getID() < id)
                low = mid + 1;
            else
            {
                if (mid == 0)
                    break;
                high = mid - 1;
            }
        }
        return SIZE_MAX;
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
        SharedPtr<Client> c(new Client());

        ss.clear();
        ss.seekp(0, std::ios::beg);
        ss.str(line);

        ss >> *c;
        c->loadSystemPtr(this);
        clients.push_back(c);
    }

    file.close();

    file.open(DRIVER_DATA_FILE_DIR, std::ios::in);

    if (!file.is_open())
        throw file_stream_error("Cannot open file!", DRIVER_DATA_FILE_DIR);

    while (!file.eof() && file.getline(line, BUFF_SIZE))
    {
        SharedPtr<Driver> d(new Driver());

        ss.clear();
        ss.seekp(0, std::ios::beg);
        ss.str(line);

        ss >> *d;
        d->loadSystemPtr(this);
        drivers.push_back(d);
    }

    file.close();
}

void System::saveData()
{
    std::ofstream file(CLIENT_DATA_FILE_DIR, std::ios::out);

    if (!file.is_open())
        throw file_stream_error("Cannot open file!", CLIENT_DATA_FILE_DIR);

    for (size_t i = 0; i < clients.size(); ++i)
        file << *clients[i] << '\n';

    file.close();

    file.open(DRIVER_DATA_FILE_DIR, std::ios::out);

    if (!file.is_open())
        throw file_stream_error("Cannot open file!", DRIVER_DATA_FILE_DIR);

    for (size_t i = 0; i < drivers.size(); ++i)
        file << *drivers[i] << '\n';

    file.close();
}

void System::addOrder(SharedPtr<Order> order)
{
    double closestDist = DBL_MAX;
    size_t idxClosestDriver = SIZE_MAX;

    if (drivers.empty())
        throw std::runtime_error("No drivers available.");

    for (size_t i = 0; i < drivers.size(); ++i)
    {
        static double dist = drivers[i]->getAddress().getDist(order->getPickupAddress());
        if (dist < closestDist)
        {
            closestDist = dist;
            idxClosestDriver = i;
        }
    }
    pendingOrders.push_back(order);
    drivers.at(idxClosestDriver)->addOrder(order);
}

void System::removeOrder(SharedPtr<Order> order)
{
    bool orderFound = false;
    if (order->isInProgress())
    {
        for (size_t i = 0; i < inProgressOrders.size(); ++i)
            if (inProgressOrders[i]->getID() == order->getID())
            {
                // Notifying the driver
                order->accessDriver()->removeOrder();
                order->accessDriver()->addMessage(
                    std::move(MyString("Attention: Order (ID ")
                                  .append(intToChar(order->getID()))
                                  .append(") has been canceled!")));

                inProgressOrders.pop_at(i);
                orderFound = true;
                break;
            }
    }
    else
    {
        for (size_t i = 0; i < pendingOrders.size(); ++i)
            if (pendingOrders[i]->getID() == order->getID())
            {
                pendingOrders.pop_at(i);
                orderFound = true;
                break;
            }
    }

    if (!orderFound)
        throw std::domain_error("Order not found in the system.");
}

void System::markOrderInProgress(size_t id)
{
    size_t idx = binarySearch(pendingOrders, id);

    if (idx == SIZE_MAX)
        throw std::runtime_error("Order not found in the system.");

    inProgressOrders.push_back(std::move(pendingOrders.at(idx)));
    pendingOrders.pop_at(idx);
}

SharedPtr<Client> System::loginClient(const char *name, const char *password)
{
    for (size_t i = 0; i < clients.size(); ++i)
    {
        if (clients[i]->getName() != name)
            continue;

        if (clients[i]->getPassword() == password)
            return clients[i];
    }

    return SharedPtr<Client>();
}
SharedPtr<Driver> System::loginDriver(const char *name, const char *password)
{
    for (size_t i = 0; i < drivers.size(); ++i)
    {
        if (drivers[i]->getName() != name)
            continue;

        if (drivers[i]->getPassword() == password)
            return drivers[i];
    }
    return SharedPtr<Driver>();
}

SharedPtr<Client> System::registerClient(const char *name, const char *password, double moneyAvailable)
{
    for (size_t i = 0; i < clients.size(); ++i)
        if (clients[i]->getName() == name)
            return SharedPtr<Client>();

    if (!validateUsername(name) || !validatePassword(password))
        return SharedPtr<Client>();

    clients.push_back(SharedPtr<Client>(new Client(MyString(name), MyString(password), moneyAvailable)));
    return clients[clients.size() - 1];
}

SharedPtr<Driver> System::registerDriver(const char *name, const char *password, const char *phoneNumber, const char *plateNumber, double moneyAvailable)
{
    for (size_t i = 0; i < drivers.size(); ++i)
        if (drivers[i]->getName() == name)
            return SharedPtr<Driver>();

    if (!validateUsername(name) || !validatePassword(password))
        return SharedPtr<Driver>();

    drivers.push_back(SharedPtr<Driver>(new Driver(MyString(name), MyString(password), moneyAvailable, Address(), MyString(phoneNumber), MyString(plateNumber))));
    return drivers[drivers.size() - 1];
}