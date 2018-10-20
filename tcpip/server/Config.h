#ifndef SERVER_CONFIG_H
#define SERVER_CONFIG_H

class Config {

public:
    static const int NUMBER_OF_READ_SYMBOLS = 5;
    static const int NUMBER_OF_CLIENTS = 5;
    static const int PORT = 7500;
    static const int HOP = 100000;
    static const char *FILE_PATH;
};

#endif //SERVER_CONFIG_H
