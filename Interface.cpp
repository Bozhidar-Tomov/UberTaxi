#include <sstream>
#include <limits>
#include "Interface.h"
#include "constants.h"
#include "MyString/Utils.h"

namespace
{
    MyString readString(std::stringstream &line)
    {
        static char buff[INPUT_BUFF_SIZE];
        line >> buff;
        return MyString(buff);
    }

    double readDouble(std::stringstream &line)
    {
        double value;
        line >> value;
        if (line.fail())
            throw std::runtime_error("Invalid input passed.");
        return value;
    }

    MyString readName(std::stringstream &line)
    {
        MyString name;
        name.append(readString(line));
        name.push_back(' ');
        name.append(readString(line));
        return name;
    }

    CommandType getCommonCommandType(const MyString &command)
    {
        if (command == "register")
            return CommandType::Register;

        if (command == "login")
            return CommandType::Login;

        if (command == "logout")
            return CommandType::Logout;

        if (command == "quit")
            return CommandType::Quit;
        return CommandType::none;
    }
}

UserType getUserType(const char *user)
{
    if (myStrCmp(user, "client") == 0)
        return UserType::Client;

    if (myStrCmp(user, "driver") == 0)
        return UserType::Driver;
    if (myStrCmp(user, "quit") == 0)
        return UserType::Quit;

    return UserType::none;
}

CommandType Interface::getCommandType(const MyString &command)
{
    if (client)
        return getClientCommandType(command);

    else if (driver)
        return getDriverCommandType(command);
    else
        return getCommonCommandType(command);
}

Address Interface::getAddress()
{
    MyString name;
    MyString descr;
    char buff[INPUT_BUFF_SIZE];

    std::cout << "Address name: ";
    std::cin.getline(buff, INPUT_BUFF_SIZE);
    name.append(buff);

    if (name.empty())
        throw std::invalid_argument("Invalid argument: Address must has a name.");

    std::cout << "Address description: ";
    std::cin.getline(buff, INPUT_BUFF_SIZE);
    descr.append(buff);

    std::cout << "Address coordinates <x y>: ";
    double x, y;
    std::cin >> x >> y;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (std::cin.fail())
    {
        std::cin.clear();
        throw std::invalid_argument("Invalid argument");
    }

    return Address(std::move(name), x, y, std::move(descr));
}

void Interface::parseLogin(std::stringstream &line)
{
    MyString name = readName(line);
    MyString password = readString(line);

    switch (userType)
    {
    case UserType::Client:
        client = sys.loginClient(name, password);
        break;
    case UserType::Driver:
        driver = sys.loginDriver(name, password);
        break;
    default:
        std::cout << "system error login <first name> <second name> <password>" << std::endl;
        return;
    }
}

void Interface::order()
{
    unsigned short passengersCount = 0;
    std::cout << "Pick up address:\n";
    Address pickUp = getAddress();

    std::cout << "\nDestination address:\n";
    Address dest = getAddress();

    std::cout << "\nNumber of passengers: \n";
    std::cin >> passengersCount;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (std::cin.fail())
    {
        std::cin.clear();
        throw std::invalid_argument("Invalid argument");
    }

    client->order(std::move(pickUp), std::move(dest), passengersCount);
}

void Interface::handleUserInput()
{
    while (true)
    {
        std::cout << std::endl
                  << (userType == UserType::Client   ? client ? *client->getName() : "Client"
                      : userType == UserType::Driver ? driver ? *driver->getName() : "Driver"
                                                     : "User")
                  << "> ";

        static char buff[INPUT_BUFF_SIZE];
        std::cin.getline(buff, INPUT_BUFF_SIZE, '\n');
        std::stringstream line(buff);

        line >> buff;
        CommandType commandType = getCommandType(MyString(buff));
        try
        {
            if (client)
                switch (commandType)
                {
                case CommandType::Logout:
                    std::cout << "==================  Guest mode  ==================" << std::endl;
                    userType = UserType::none;
                    client.reset();
                    return;
                case CommandType::Order:
                    order();
                    std::cout << "Successful order." << '\n';
                    break;
                case CommandType::CheckOrder:
                    client->checkOrder();
                    break;
                case CommandType::CancelOrder:
                    client->cancelOrder();
                    std::cout << "Order canceled." << '\n';
                    break;
                case CommandType::Pay:
                {
                    double amount = client->pay();
                    std::cout << "Successful payment of " << amount << '\n';
                    break;
                }
                case CommandType::Rate:
                {
                    static unsigned short rating;
                    line >> rating;
                    static bool called = false;

                    if (rating == 0 || rating > 5)
                    {
                        std::cout << "Invalid rating";
                        break;
                    }

                    if (called)
                    {
                        std::cout << "Driver already rated with " << rating << " stars.\n";
                        break;
                    }

                    client->rateDriver(rating);
                    called = true;

                    std::cout << "Successful rating.";
                    break;
                }
                case CommandType::AddMoney:
                {
                    double amount;
                    line >> amount;

                    if (line.fail() || amount < EPSILON)
                    {
                        std::cout << "Invalid amount.\n";
                        break;
                    }

                    client->addMoney(amount);
                    std::cout << "Successfully added " << amount << '\n';
                    break;
                }
                default:
                    std::cout << "Command not found.\n";
                    break;
                }

            else if (driver)
                switch (commandType)
                {
                case CommandType::Logout:
                    userType = UserType::none;
                    driver.reset();
                    std::cout << "================== Guest mode ==================" << std::endl;
                    return;
                case CommandType::ChangeAddress:
                    driver->changeCurrAddress(getAddress());
                    std::cout << "Address changed.\n";
                    break;
                case CommandType::GetMessages:
                    driver->getMessages();
                    break;
                case CommandType::GetAvailableOrders:
                    driver->checkAvailableOrders();
                    break;
                case CommandType::AcceptOrder:
                {
                    size_t ID;
                    unsigned short minutes;
                    line >> ID;
                    line >> minutes;

                    if (line.fail())
                    {
                        std::cout << "Invalid input\n";
                        break;
                    }

                    driver->acceptOrder(ID, minutes);
                    std::cout << "Order accepted\n";
                    break;
                }
                case CommandType::DeclineOrder:
                {
                    size_t ID;
                    line >> ID;

                    if (line.fail())
                    {
                        std::cout << "Invalid input\n";
                        break;
                    }

                    driver->declineOrder(ID);
                    std::cout << "Order declined\n";
                    break;
                }
                case CommandType::FinishOrder:
                {
                    driver->finishOrder();
                    std::cout << "Order marked as finished.\n";
                    break;
                }
                default:
                    std::cout << "Command not found." << std::endl;
                    break;
                }
            else
                switch (commandType)
                {
                case CommandType::Login:
                    parseLogin(line);
                    break;
                case CommandType::Register:
                    parseRegister(line);
                    break;
                case CommandType::Quit:
                    std::cout << "==================  Guest mode  ==================" << std::endl;
                    return;
                default:
                    std::cout << "Command not found." << std::endl;
                    break;
                }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
}

void Interface::run()
{
    std::cout << "==================  Welcome  ==================" << std::endl;

    while (true)
    {
        std::cout << "\nGuest> ";
        static char buff[INPUT_BUFF_SIZE];
        std::cin.getline(buff, INPUT_BUFF_SIZE, '\n');

        userType = getUserType(buff);
        std::stringstream line(buff);

        switch (userType)
        {
        case UserType::Client:
        {
            std::cout << "==================  Client mode  ==================" << std::endl;
            break;
        }

        case UserType::Driver:
            std::cout << "==================  Driver mode  ==================" << std::endl;
            break;
        case UserType::Quit:
            sys.saveData();
            std::cout << "System state saved successfully." << std::endl;
            return;

        default:
            std::cout << "Invalid user type: " << buff << std::endl;
            continue;
        }

        handleUserInput();
    }
}

void Interface::parseRegister(std::stringstream &line)
{
    MyString name = readName(line);
    MyString password = readString(line);

    switch (userType)
    {
    case UserType::Client:
        client = sys.registerClient(std::move(name), std::move(password));
        break;

    case UserType::Driver:
    {
        MyString phoneNumber = readString(line);
        MyString plateNumber = readString(line);
        double chargePerKm = readDouble(line);

        driver = sys.registerDriver(std::move(name), std::move(password), std::move(phoneNumber), std::move(plateNumber), 0, chargePerKm);
        break;
    }

    default:
    {
        std::cout << "Invalid input" << '\n';
        break;
    }
    }
}