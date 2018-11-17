
#include <tgmath.h>
#include "Client.h"


Client::Client() {
    peer.sin_family = AF_INET;
    peer.sin_port = htons(Config::PORT);
    peer.sin_addr.s_addr = inet_addr(Config::INET_ADDR);

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
}

int Client::openConnection() {
    int c = connect(serverSocket, (struct sockaddr *)&peer, sizeof(peer));
    if (c < 0) {
        std::cout << "Fail to connect !!!" << std::endl;
    } else {
        std::cout << "Client connect to " << Config::INET_ADDR << " " << Config::PORT << std::endl;
    }
    return c;
}

void Client::closeConnection() {
    write("EXIT?");
    shutdown(serverSocket, SHUT_RDWR);
    close(serverSocket);
    std::cout << "Connection was closed" << std::endl;
}

void Client::write(std::string data) {
    size_t sizeOfBuffer = (size_t) Config::NUMBER_OF_READ_SYMBOLS;
    send(serverSocket, data.c_str(), sizeOfBuffer, 0);
}

std::string Client::read() {
    return Utility::read_delimiter(serverSocket);
}

std::vector<long> Client::countSimpleNumbers(std::pair<long, long> range) {
    std::vector<long> result;
    if (range.first == 0) {
        result.push_back(2);
        range.first = 2;
    }
    bool isSimple;
    for (long num = range.first+1; num < range.second; num+=2) {
        isSimple = true;  //9 25 49
        for (long j = 3; j <= sqrt(num); j+=2) {
            if (num % j == 0) {
                isSimple = false;
                break;
            }
        }
        if (isSimple) {
            result.push_back(num);
        }
    }
    return result;
}

