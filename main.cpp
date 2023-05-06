#include "MyString/MyString.h"
#include "User.h"

int main()
{
    MyString r("password");
    User user2(MyString("hello world"), std::move(r), 25);

    r.append("f");
}