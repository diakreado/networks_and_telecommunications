#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <mutex>
#include <vector>
#include <zconf.h>
#include <algorithm>
#include <iostream>
#include "Config.h"
#include "ConsoleHandler.h"

class Server {

public:
    Server();
    ~Server() = default;

    int start();

    static std::vector<int> getArrayOfConnection();

private:
    static int acceptSocket;

    static ConsoleHandler ch;
    static std::mutex mtx;
    static std::vector<int> arrayOfConnection;

    static void acceptThread();
    static void threadFunc(int* data);
    static int read_n(int n, int s1, char *result);
};

#endif //SERVER_SERVER_H
