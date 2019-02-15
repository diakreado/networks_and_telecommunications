#ifndef SERVER_CONFIG_H
#define SERVER_CONFIG_H

class Config {

public:
    static const int NUMBER_OF_READ_SYMBOLS = 50;
    static const int ACKNOWLEDGE_LEN = 5;
    static const int PORT = 7500;
    static const int HOP = 10;
    static const char DELIMITER = ';';
    static const char *FILE_PATH;
    static const char *INET_ADDR;
    static const int APPROXIMATE_NUMBER_OF_CLIENTS = 5;
};

#endif //SERVER_CONFIG_H
