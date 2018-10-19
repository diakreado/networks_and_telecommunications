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

#include "ConsoleHandler.h"
#include "Config.h"

#include <malloc.h>


typedef struct {
    int client_sockets[Config::NUMBER_OF_CLIENTS];
    char action;
} pthrData;


class Server {

public:

    Server();
    void start();

private:

    static int acceptSocket;

    static std::mutex mtx;
    static std::vector<int> arrayOfConnection;

    static void acceptThread(pthrData* data);
    static void threadFunc(int* data);
    static int read_n(int n, int s1, char *result);
};

#endif //SERVER_SERVER_H
