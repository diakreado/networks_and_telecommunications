#ifndef TCPIP_REQUESTHANDLER_H
#define TCPIP_REQUESTHANDLER_H


#include <iostream>
#include <string>
#include "../Utility.h"

class RequestHandler {

public:
    static void handle(int socket, std::string request);
};


#endif //TCPIP_REQUESTHANDLER_H
