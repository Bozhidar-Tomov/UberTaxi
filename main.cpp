#include <iostream>
#include "MyString/MyString.h"
#include "MyVector/MyVector.h"
#include "Users/Client.h"
#include "System.h"
#include "Address.h"
#include "SmartPointers/SharedPtr.hxx"
#include "SmartPointers/UniquePtr.hxx"

int main()
{
    System sys;

    sys.loadData();

    SharedPtr<Client> r = sys.clients[0];

    SharedPtr<Client> client = sys.loginClient("new name", "P@ssword1");

    client->order(Address(MyString("addrs"), 5, 5, MyString("descr")), Address(MyString("addrs"), 50, 50, MyString("descr")), 9);
    client->order(Address(MyString("ADDR"), 50, 50, MyString("DESCR")), Address(MyString("ADDR"), 5, 5, MyString("DESCR")), 15);

    SharedPtr<Driver> driver = sys.loginDriver("new name", "P@ssword1");

    driver->checkAvailableOrders();
    driver->acceptOrder(2, 25);

    for (int i = 0; i < sys.inProgressOrders.size(); ++i)
    {
        std::cout << *sys.inProgressOrders[i] << " mins: " << sys.inProgressOrders[i]->getArriveIn() << '\n';
    }
}