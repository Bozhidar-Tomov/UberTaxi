#include <iostream>
#include "MyString/MyString.h"
#include "MyVector/MyVector.h"
#include "Users/Client.h"
#include "System.h"

int main()
{
    MyString n1("name1");
    MyString n2("name2");
    MyString n3("name3");

    // [x]: use vector.push_back()
    MyVector<MyString> vec1;
    MyVector<User> vec2;

    Client u("he", "he", 2);
    // vec1.push_back(n1);
    // vec2.push_back(u);

    // MyVector<Client> vec(3);
    // vec.push_back(u);
    // vec.push_back(u);

    // User user2(MyString(" hello world "), MyString("hello world"), 25, 0);
    //     int money[]{1, 2, 3, 4, 5, 6};
    //     user2.deleteAccount(vec, vec, money);

    //     // User nk = login("name2", "pass", vec, vec, money);

    System sys;

    sys.loadData();
    sys.clients.at(3).setName("__________________");
    sys.saveData();
    std::cout << sys.clients[0];

    int stop = 0;
}