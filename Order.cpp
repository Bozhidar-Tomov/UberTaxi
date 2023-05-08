#include "Order.h"
#include "iostream"

Order::Order(const char *address, const char *dest, const Client *client, const Driver *driver) : _address(address), _dest(dest), _client(client), _driver(driver)
{
    if (!address || !dest || !client || !driver)
        throw std::invalid_argument("Invalid arguments provided (nullptr).");
}

Order::Order(const MyString &address, const MyString &dest, const Client *client, const Driver *driver) : _address(address), _dest(dest), _client(client), _driver(driver)
{
    if (!client || !driver)
        throw std::invalid_argument("Invalid arguments provided (nullptr).");
}

void Order::changeAddress(const char *newAddress)
{
    _address.reset_data();
    _address.append(newAddress);
}
