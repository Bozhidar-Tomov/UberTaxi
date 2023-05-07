#include <iostream>
#include "MyString/MyString.h"
#include "VectorString/VectorString.h"
#include "User.h"

int main()
{
    MyString r("password");

    VectorString vec(32);
    vec.push_back(r);

    std::cout << vec[0];

    User user2(MyString("hello world"), std::move(r), 25);
}