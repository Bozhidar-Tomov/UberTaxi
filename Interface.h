#pragma once

#include "System.h"
#include "Commands/Command.h"

class Interface
{
    System sys;
    SharedPtr<Client> client;
    SharedPtr<Driver> driver;
    MyVector<Command> commands;
    UserType userType = UserType::none;

    CommandType getCommandType(const MyString &command);

    Address getAddress();
    void parseRegister(std::stringstream &);
    void parseLogin(std::stringstream &);
    void order();

    void handleUserInput();

public:
    Interface() : sys(System::getInstance()){};
    void run();
};