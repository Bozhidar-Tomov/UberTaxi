#pragma once

const char CLIENTS_DATA_FILE_DIR[] = "Data/clientsData.txt";
const char DRIVERS_DATA_FILE_DIR[] = "Data/driversData.txt";
const char ORDERS_DATA_FILE_DIR[] = "Data/ordersData.txt";
const char STATISTICS_DATA_FILE_DIR[] = "Data/statisticsData.dat";
const char LINE_SEPARATOR[] = "---------------------------------------------------------------------";
const unsigned MAX_NAME_LEN = 20;
const unsigned MIN_NAME_LEN = 3;

const unsigned MAX_PASSWORD_LEN = 30;
const unsigned MIN_PASSWORD_LEN = 8;

const unsigned MAX_NUM_LEN = 9;
const char DELIM = '|';

// Adding +1 and +1 for the two delimiters and +1 for '\0' at the end
const unsigned BUFF_SIZE = MAX_PASSWORD_LEN + 1 + MAX_NAME_LEN + 1 + MAX_NUM_LEN + 1;
const unsigned INPUT_BUFF_SIZE = 512;

const unsigned short MESSAGE_COUNT = 5;

enum class UserType
{
    Client,
    Driver,
    Quit,

    none,
};

enum class CommandType
{
    Login,
    Register,
    Logout,
    Quit,

    Order,
    CheckOrder,
    CancelOrder,
    Pay,
    Rate,
    AddMoney,

    ChangeAddress,
    GetMessages,
    GetAvailableOrders,
    AcceptOrder,
    DeclineOrder,
    FinishOrder,

    none,
};
