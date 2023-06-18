#include "Interface.h"
#include "constants.h"
#include "MyString/Utils.h"
#include <sstream>

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
            throw std::runtime_error("Invalid input passed. (throw)");
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

}

// void Interface::handleExceptions(void (Interface::*func)(const char *), const char *input) noexcept
// {
//     try
//     {
//         (this->*func)(input);
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "Exception handle Error: " << e.what() << std::endl;
//     }
// }

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
    if (command == "register")
        return CommandType::Register;

    if (command == "login")
        return CommandType::Login;

    if (command == "logout")
        return CommandType::Logout;

    if (command == "quit")
        return CommandType::Quit;

    if (userType == UserType::Client)
        return getClientCommandType(command);

    if (userType == UserType::Driver)
        return getDriverCommandType(command);

    return CommandType::none;
}

Address Interface::getAddress()
{
    MyString name;
    MyString descr;
    char buff[INPUT_BUFF_SIZE];

    std::cout << "Address name: ";
    std::cin.getline(buff, INPUT_BUFF_SIZE);
    name.append(buff);

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

// BUG cyclic shared ptrs! client->order order->client
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
        throw std::runtime_error("Invalid input.");

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
                {
                    client.reset();
                    return;
                }
                case CommandType::Order:
                    order();
                    break;
                case CommandType::CheckOrder:
                    client->checkOrder();
                    break;
                case CommandType::CancelOrder:
                    // [x] deleting5Order ???
                    client->cancelOrder();
                    break;
                case CommandType::Pay:
                    client->pay();
                    break;
                case CommandType::Rate:
                {
                    unsigned short rating;
                    line >> rating;

                    client->rateDriver(rating);
                    break;
                }
                case CommandType::AddMoney:
                {
                    double amount;
                    line >> amount;

                    client->addMoney(amount);
                    break;
                }
                case CommandType::Quit:
                    return;
                default:
                    std::cout << "Command not found." << std::endl;
                    break;
                }
            else if (driver)
                switch (commandType)
                {
                case CommandType::Logout:
                    driver.reset();
                    return;
                case CommandType::ChangeAddress:
                    driver->changeCurrAddress(getAddress());
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

                    driver->acceptOrder(ID, minutes);
                    break;
                }
                case CommandType::DeclineOrder:
                {
                    size_t ID;
                    line >> ID;

                    driver->declineOrder(ID);
                    break;
                }
                case CommandType::FinishOrder:
                {
                    driver->finishOrder();
                    break;
                }
                case CommandType::Quit:
                    return;
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

Interface::Interface()
{
    sys.loadData();
}

void Interface::run()
{
    std::cout << "==================  Guest mode  ==================" << std::endl;
    std::cout << "<user type>" << std::endl;

    while (true)
    {
        std::cout << "Guest> ";
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
            return;

        default:
            std::cout << "Invalid user type: " << buff << std::endl;
            continue;
        }

        handleUserInput();

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
        throw std::runtime_error("Invalid input passed. (throw)");
    }
}