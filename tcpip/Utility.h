#ifndef TCPIP_UTILITY_H
#define TCPIP_UTILITY_H


#include <string>
#include <vector>
#include <sstream>
#include <sys/socket.h>
#include "Config.h"


class Utility {

public:
    static void split(std::string str, std::vector<std::string>& cont, char divider);
    static int read_n(int s1, char *result);
    static std::string read_delimiter(int s1);
};


#endif //TCPIP_UTILITY_H
