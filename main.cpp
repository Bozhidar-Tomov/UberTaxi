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

    client->order(Address(MyString("addrs"), 5, 5, MyString("descr")), Address(MyString("addrs"), 5, 5, MyString("descr")), 9);
}