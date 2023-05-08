const char CLIENT_DATA_FILE_DIR[] = "Data/clientData.dat";
const char DRIVER_DATA_FILE_DIR[] = "Data/driverData.dat";
const unsigned MAX_NAME_LEN = 50;
const unsigned MAX_PASSWORD_LEN = 30;
const unsigned MAX_NUM_LEN = 9;
const char DELIM = '|';

// Adding +1 and +1 for the two delimiters and +1 for '\0' at the end
const unsigned BUFF_SIZE = MAX_PASSWORD_LEN + 1 + MAX_NAME_LEN + 1 + MAX_NUM_LEN + 1;
