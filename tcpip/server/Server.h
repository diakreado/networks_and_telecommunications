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
#include "../Config.h"
#include "ConsoleHandler.h"
#include "model/SimpleNumbers.h"
#include "RequestHandler.h"

class Server {

public:
    explicit Server();
    ~Server() = default;

    int start();

    static std::vector<int> getArrayOfConnection();
    static void write(const int clientSocket, std::string data);

private:
    static int acceptSocket;

    static ConsoleHandler consoleH;
    static RequestHandler requestH;
    static SimpleNumbers* model;
    static std::mutex mtx;
    static std::vector<int> arrayOfConnection;

    static void acceptThread();
    static void threadFunc(int* data);
};

#endif //SERVER_SERVER_H
