
#ifndef TCPIP_CLIENT_H
#define TCPIP_CLIENT_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <zconf.h>
#include <string>
#include <iostream>
#include "ClientConfig.h"


class Client {

public:
    Client();
    void openConnection();
    void closeConnection();
    void write(std::string data);
    std::string read();

private:

    int clientSocket;
    struct sockaddr_in peer;

};


#endif //TCPIP_CLIENT_H
