#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <thread>
#include <mutex>
#include <vector>
#include <unistd.h>
#include <algorithm>
#include <iostream>
#include "../Config.h"
#include "RequestHandler.h"
#include <stdlib.h>
#include <string.h>

class Server {

public:
    explicit Server();
    ~Server() = default;

    int start();

    static void write(struct sockaddr_in si_other, std::string data);
    static void closeConnection(int socket);
    static int getServerSocket();

private:
    static int serverSocket;
    static std::string command;

    static void mainThread();
    static void threadFunc(struct sockaddr_in si_other, std::string data);

    static void error_message(char* s);
};

#endif //SERVER_SERVER_H
