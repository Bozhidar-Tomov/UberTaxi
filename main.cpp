#include <iostream>
#include "MyString/MyString.h"
#include "MyVector/MyVector.h"
#include "Users/Client.h"
#include "System.h"
#include "Address.h"
#include "SmartPointers/SharedPtr.hxx"

int main()
{
    System sys;
    sys.loadData();

    SharedPtr<Client> client = sys.registerClient("New Client", "P@ssword1", 100);
    // SharedPtr<Client> client = sys.loginClient("new name", "P@ssword1");
    SharedPtr<Driver> driver = sys.registerDriver("New name", "P@ssword1", "phone num", "plate num", 100, 1.2);
    // SharedPtr<Driver> driver = sys.loginDriver("new name", "P@ssword1");

    client->order(Address(MyString("addrs"), 5, 5, MyString("descr")), Address(MyString("addrs"), 50, 50, MyString("descr")), 9);

    driver->checkAvailableOrders();
    driver->acceptOrder(1, 25);
    driver->finishOrder();

    client->rateDriver(3);
    client->pay();

    sys.saveData();

    // driver->declineOrder(1);
    // client->checkOrder();
    // client->cancelOrder();
    // driver->getMessages();

    // for (int i = 0; i < sys.inProgressOrders.size(); ++i)
    // {
    //     std::cout << *sys.inProgressOrders[i] << " mins: " << sys.inProgressOrders[i]->getArriveIn() << '\n';
    // }
}