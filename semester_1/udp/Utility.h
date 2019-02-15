#ifndef TCPIP_UTILITY_H
#define TCPIP_UTILITY_H


#include <string>
#include <vector>
#include <sstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include "Config.h"
#include <sys/ioctl.h>


class Utility {

public:
    static void split(const std::string &str, std::vector<std::string> &cont, char divider);
};


#endif //TCPIP_UTILITY_H
