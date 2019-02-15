
#include <iostream>
#include "Utility.h"

void Utility::split(const std::string &str, std::vector<std::string> &cont, const char divider) {
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, divider)) {
        cont.push_back(token);
    }
}

