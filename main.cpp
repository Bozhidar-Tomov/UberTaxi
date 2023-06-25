#include <iostream>
#include "Interface.h"

int main()
{
    try
    {
        Interface program;
        program.run();
    }
    catch (std::exception &e)
    {
        std::cout << e.what();
    }
}

// TODO save user address