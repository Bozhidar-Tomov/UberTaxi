#include <iostream>
#include "MyString/MyString.h"
#include "MyVector/MyVector.h"
#include "Users/User.h"

int main()
{
    MyString n1("name1");
    MyString n2("name2");
    MyString n3("name3");

    MyVector<MyString> vec1;
    MyVector<User> vec2;

    User u("he", "he", 2, 5);
    vec1.push_back(n1);
    vec2.push_back(u);

    //     VectorString vec(3);
    //     vec.push_back(n1);
    //     vec.push_back(n2);
    //     vec.push_back(n3);

    // User user2(MyString(" hello world "), MyString("hello world"), 25, 0);
    //     int money[]{1, 2, 3, 4, 5, 6};
    //     user2.deleteAccount(vec, vec, money);

    //     // User nk = login("name2", "pass", vec, vec, money);
}