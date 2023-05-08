#include "System.h"
#include "constants.h"
#include "Exceptions/file_stream_error.h"
#include "Utils.h"
#include <fstream>
#include <iostream>

// TODO: do the logic of drivers as well (load)
void System::loadData()
{
    // BUG: new line in the end of file can cause bugs
    std::ifstream file(CLIENT_DATA_FILE_DIR, std::ios::in);

    if (!file.is_open())
    {
        std::cout << "ERROR FILE";
        throw file_stream_error("Cannot open file!", CLIENT_DATA_FILE_DIR);
    }

    // TODO: try using/defining operator>>
    int idx = 0;
    static std::stringstream ss;
    static char line[BUFF_SIZE]{'\0'};

    while (!file.eof())
    {
        ++idx;

        file.getline(line, BUFF_SIZE);

        ss.clear();
        ss.seekp(0, std::ios::beg);
        ss.str(line);

        // FIXME: make sure that move semantics are called!
        clients.push_back(std::move(parseLine(ss)));
    }

    file.close();
}

// TODO: do the logic of drivers as well (save)
void System::saveData()
{
    // BUG: new line in the end of file can cause bugs
    std::ofstream file(CLIENT_DATA_FILE_DIR, std::ios::out);

    if (!file.is_open())
        throw file_stream_error("Cannot open file!", CLIENT_DATA_FILE_DIR);

    static std::stringstream ss;

    for (size_t i = 0; i < clients.size(); ++i)
    {
        file << clients[i] << '\n';
    }

    file.close();
}

// TODO: make parseLine for driver
Client System::parseLine(std::stringstream &stream)
{
    Client client;

    static char line[BUFF_SIZE]{'\0'};

    stream.getline(line, BUFF_SIZE, DELIM);
    client.setName(line);

    stream.getline(line, BUFF_SIZE, DELIM);
    client.setPassword(line);

    stream.getline(line, BUFF_SIZE, DELIM);
    client.setMoneyAvailable(strToDouble(line));

    return client;
}
