#include <iostream>
#include "MyString/MyString.h"
#include "MyVector/MyVector.h"
#include "Users/Client.h"
#include "System.h"
#include "Address.h"
#include "SmartPointers/SharedPtr.hxx"

int main()
{
    {
        std::cout << "Address:" << sizeof(Address) << '\n';
        std::cout << "MyVector:" << sizeof(MyVector<Client *>) << '\n';
        std::cout << "Client:" << sizeof(Client) << '\n';
        std::cout << "Driver:" << sizeof(Driver) << '\n';
    }
}