#ifndef TCPIP_UTILITY_H
#define TCPIP_UTILITY_H


#include <string>
#include <vector>
#include <sstream>


class Utility {

public:
    static void split(std::string str, std::vector<std::string>& cont, char divider);

};


#endif //TCPIP_UTILITY_H
