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

    bool validateName(const char *name)
    {
        const char *begin = name;

        if (!name || !*name || !isUpper(*name))
            return false;

        while (isAlpha(*(++name)))
            ;

        if (!isSpace(*name))
            return false;

        while (!isAlpha(*(++name)))
            ;

        if (name - begin > MAX_NAME_LEN || name - begin < MIN_NAME_LEN)
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

    template <typename T>
    size_t binarySearch(T &container, size_t id)
    {
        size_t low = 0;
        size_t high = container.size() - 1;

        while (low <= high)
        {
            size_t mid = low + (high - low) / 2;

            if (container[mid]->getID() == id)
                return mid;

            if (container[mid]->getID() < id)
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
    std::ifstream file(CLIENTS_DATA_FILE_DIR, std::ios::in);

    if (!file.is_open())
        throw file_stream_error("Cannot open file!", CLIENTS_DATA_FILE_DIR);

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

    file.open(DRIVERS_DATA_FILE_DIR, std::ios::in);

    if (!file.is_open())
        throw file_stream_error("Cannot open file!", DRIVERS_DATA_FILE_DIR);

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

    file.open(STATISTICS_DATA_FILE_DIR, std::ios::binary);

    file.read(reinterpret_cast<char *>(&profit), sizeof(profit));
    file.read(reinterpret_cast<char *>(&driversCount), sizeof(driversCount));
    file.read(reinterpret_cast<char *>(&clientsCount), sizeof(clientsCount));
    file.read(reinterpret_cast<char *>(&ordersCount), sizeof(ordersCount));

    file.close();
}

void System::saveData()
{
    std::ofstream file(CLIENTS_DATA_FILE_DIR, std::ios::out);

    if (!file.is_open())
        throw file_stream_error("Cannot open file!", CLIENTS_DATA_FILE_DIR);

    for (size_t i = 0; i < clients.size(); ++i)
        file << *clients[i] << '\n';

    file.close();

    file.open(DRIVERS_DATA_FILE_DIR, std::ios::out);

    if (!file.is_open())
        throw file_stream_error("Cannot open file!", DRIVERS_DATA_FILE_DIR);

    for (size_t i = 0; i < drivers.size(); ++i)
        file << *drivers[i] << '\n';

    file.close();

    file.open(ORDERS_DATA_FILE_DIR, std::ios::app);
    if (!file.is_open())
        throw file_stream_error("Cannot open file!", ORDERS_DATA_FILE_DIR);

    for (size_t i = 0; i < finishedOrders.size(); ++i)
        file << *finishedOrders[i] << '\n';

    file.close();

    saveStatistics();
}

void System::addOrder(SharedPtr<Order> order)
{
    if (drivers.empty())
        throw std::runtime_error("No drivers available.");

    pendingOrders.push_back(order);
    notifyClosestDriver(order);
}

void System::notifyClosestDriver(SharedPtr<Order> order, Driver *excludedDriver)
{
    double closestDist = DBL_MAX;
    static double dist = DBL_MAX;
    size_t idxClosestDriver = SIZE_MAX;

    for (size_t i = 0; i < drivers.size(); ++i)
    {
        if (excludedDriver && drivers[i].get() == excludedDriver)
            continue;

        dist = drivers[i]->getAddress().getDist(order->getPickupAddress());
        if (dist < closestDist)
        {
            closestDist = dist;
            idxClosestDriver = i;
        }
    }

    if (idxClosestDriver == SIZE_MAX)
        throw std::runtime_error("No drivers available.");

    drivers.at(idxClosestDriver)->addOrder(order);
}

void System::removeOrder_clientCall(SharedPtr<Order> order) // experimental
{
    if (order->isInProgress())
        for (size_t i = 0; i < inProgressOrders.size(); ++i)
            if (inProgressOrders[i]->getID() == order->getID())
            {
                // Notifying the driver
                order->changeStatus(OrderStatus::Canceled);
                order->accessDriver()->removeOrder();
                order->accessDriver()->addMessage(
                    std::move(MyString("Attention: Order (ID ")
                                  .append(intToChar(order->getID()))
                                  .append(") has been canceled!")));

                inProgressOrders.pop_at(i);
                return;
            }

    if (order->isPending())
        for (size_t i = 0; i < pendingOrders.size(); ++i)
            if (pendingOrders[i]->getID() == order->getID())
            {
                order->changeStatus(OrderStatus::Canceled);
                pendingOrders.pop_at(i);
                return;
            }

    throw std::domain_error("Order not found in the system.");
}

void System::finishOrder(SharedPtr<Order> order)
{
    order->changeStatus(OrderStatus::Finished);
    for (size_t i = 0; i < inProgressOrders.size(); ++i)
        if (inProgressOrders[i]->getID() == order->getID())
        {
            inProgressOrders.pop_at(i);
            finishedOrders.push_back(order);
            ++ordersCount;
            return;
        }

    throw std::domain_error("Order not found in the system.");
}

void System::releaseOrder(SharedPtr<Order> order)
{
    order->accessDriver()->removeOrder();
    order->accessClient()->removeOrder();
}

void System::addProfit(double profit)
{
    this->profit += profit;
}

void System::markOrderInProgress(size_t orderID)
{
    size_t idx = binarySearch(pendingOrders, orderID);

    if (idx == SIZE_MAX)
        throw std::runtime_error("Order not found in the system.");

    pendingOrders.at(idx)->changeStatus(OrderStatus::InProgress);
    inProgressOrders.push_back(std::move(pendingOrders.at(idx)));
    pendingOrders.pop_at(idx);
}

void System::resetStatistics()
{
    profit = 0;
    driversCount = clientsCount = ordersCount = 0;
}

SharedPtr<Client> System::loginClient(const char *name, const char *password)
{
    for (size_t i = 0; i < clients.size(); ++i)
    {
        if (clients[i]->getName() != name)
            continue;

        if (clients[i]->getPassword() == password)
            return clients[i];

        std::invalid_argument("Wrong password.");
    }
    throw std::invalid_argument("Client with this name not found.");
}
SharedPtr<Driver> System::loginDriver(const char *name, const char *password)
{
    for (size_t i = 0; i < drivers.size(); ++i)
    {
        if (drivers[i]->getName() != name)
            continue;

        if (drivers[i]->getPassword() == password)
            return drivers[i];

        std::invalid_argument("Wrong password.");
    }
    throw std::invalid_argument("Driver with this name not found.");
}

SharedPtr<Client> System::registerClient(const char *name, const char *password, double moneyAvailable)
{
    for (size_t i = 0; i < clients.size(); ++i)
        if (clients[i]->getName() == name)
            return SharedPtr<Client>();

    if (!validateName(name) || !validatePassword(password))
        return SharedPtr<Client>();

    clients.push_back(SharedPtr<Client>(new Client(MyString(name), MyString(password), moneyAvailable, this)));
    ++clientsCount;

    return clients[clients.size() - 1];
}

SharedPtr<Driver> System::registerDriver(const char *name, const char *password, const char *phoneNumber,
                                         const char *plateNumber, double moneyAvailable, double chargePerKm)
{
    for (size_t i = 0; i < drivers.size(); ++i)
        if (drivers[i]->getName() == name)
            throw std::logic_error("Driver with this name already exists.");

    if (!validateName(name) || !validatePassword(password))
        throw std::invalid_argument("Invalid name or password");

    drivers.push_back(SharedPtr<Driver>(
        new Driver(MyString(name), MyString(password), moneyAvailable, this,
                   Address(), MyString(phoneNumber), MyString(plateNumber), chargePerKm)));
    ++driversCount;

    return drivers[drivers.size() - 1];
}

void System::saveStatistics() const
{
    std::ofstream file(STATISTICS_DATA_FILE_DIR, std::ios::binary);

    if (!file.is_open())
        throw file_stream_error("Cannot open file!", STATISTICS_DATA_FILE_DIR);

    file.write(reinterpret_cast<const char *>(&profit), sizeof(profit));
    file.write(reinterpret_cast<const char *>(&driversCount), sizeof(driversCount));
    file.write(reinterpret_cast<const char *>(&clientsCount), sizeof(clientsCount));
    file.write(reinterpret_cast<const char *>(&ordersCount), sizeof(ordersCount));

    file.close();
}
