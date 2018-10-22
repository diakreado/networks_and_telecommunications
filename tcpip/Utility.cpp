
#include <iostream>
#include "Utility.h"

void Utility::split(const std::string str, std::vector<std::string> &cont, const char divider) {
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, divider)) {
        cont.push_back(token);
    }
}

int Utility::read_n(int s1, char *result) {
    char buf[1];
    int number_of_entered = 0;
    ssize_t rc = -1;

    while (number_of_entered != Config::NUMBER_OF_READ_SYMBOLS) {
        rc = recv(s1, buf, 1, 0);
        if (rc == -1) {
            break;
        }
        result[number_of_entered] = buf[0];
        number_of_entered += rc;
    }
    return (int) rc;
}


std::string Utility::read_delimiter(int s1) {
    char buf[1];
    int number_of_entered = 0;
    std::string outData;
    ssize_t rc = -1;

    while (buf[0] != Config::DELIMITER) {
        rc = recv(s1, buf, 1, 0);
        if (buf[0] == 0) {
            continue;
        }
        if (rc == -1) {
            break;
        }
        outData.push_back(buf[0]);
        number_of_entered += rc;
    }
    return outData;
}