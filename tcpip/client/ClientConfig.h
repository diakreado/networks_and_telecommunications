
#ifndef TCPIP_CLIENTCONFIG_H
#define TCPIP_CLIENTCONFIG_H

#include "../server/Config.h"

class ClientConfig {

public:
    static const int NUMBER_OF_CLIENTS = 10;
    static const int PORT = Config::PORT;
    static const char *INET_ADDR;
};


#endif //TCPIP_CLIENTCONFIG_H
