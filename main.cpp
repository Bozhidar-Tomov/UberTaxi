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
        SharedPtr<int> r;
        int *i = new int(6);
        r.reset(i);

        SharedPtr<int> a = std::move(r);
        SharedPtr<int> s(nullptr);

        s.swap(r);
    }
}