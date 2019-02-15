
#ifndef TCPIP_CLIENT_H
#define TCPIP_CLIENT_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>
#include <tgmath.h>
#include <unistd.h>
#include <cstring>
#include "../Config.h"
#include "../Utility.h"


class Client {

public:
    Client();
    void closeConnection();
    void write(std::string data);
    std::string read();
    std::vector<long > countSimpleNumbers(std::pair<long,long> range);
    int getServerSocket();
    bool isServerReachable();

private:
    int serverSocket;
    struct sockaddr_in peer;
};


#endif //TCPIP_CLIENT_H
