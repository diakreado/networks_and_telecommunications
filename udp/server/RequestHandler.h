#ifndef TCPIP_REQUESTHANDLER_H
#define TCPIP_REQUESTHANDLER_H


#include <iostream>
#include <string>
#include "../Utility.h"
#include "model/SimpleNumbers.h"

class RequestHandler {

public:
    static void handle(struct sockaddr_in si_other, std::string request);

private:
    static SimpleNumbers* model;
};


#endif //TCPIP_REQUESTHANDLER_H
