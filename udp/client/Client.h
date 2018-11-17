
#ifndef TCPIP_CLIENT_H
#define TCPIP_CLIENT_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//#include <zconf.h>
#include <string>
#include <iostream>
#include "../Config.h"
#include "../Utility.h"


class Client {

public:
    Client();
    int openConnection();
    void closeConnection();
    void write(std::string data);
    std::string read();
    std::vector<long > countSimpleNumbers(std::pair<long,long> range);

private:
    int serverSocket;
    struct sockaddr_in peer;
};


#endif //TCPIP_CLIENT_H
