#include <iostream>
#include "Interface.h"

int main()
{
    try
    {
        Interface program;
        program.run();
    }
    catch (const std::exception &e)
    {
    }
}