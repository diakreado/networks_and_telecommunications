
#include "Client.h"


Client::Client() {
    peer.sin_family = AF_INET;
    peer.sin_port = htons(Config::PORT);
    peer.sin_addr.s_addr = INADDR_ANY;

    if ( (clientSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
}

void Client::closeConnection() {
    write("EXIT?");
    shutdown(clientSocket, SHUT_RDWR);
    close(clientSocket);
    std::cout << "Connection was closed" << std::endl;
}

void Client::write(std::string data) {
    size_t sizeOfBuffer = (size_t) Config::NUMBER_OF_READ_SYMBOLS;

    sendto(clientSocket, data.c_str(), sizeOfBuffer,
           0, (const struct sockaddr *) &peer, sizeof(peer));
}

std::string Client::read() {
    char buffer[Config::NUMBER_OF_READ_SYMBOLS];
    ssize_t rc = -1;
    socklen_t slen = sizeof(peer);

    rc = recvfrom(clientSocket, (char *)buffer, Config::NUMBER_OF_READ_SYMBOLS,
                 0, (struct sockaddr *) &peer, &slen);

    std::vector<std::string> result;
    Utility::split(buffer, result, ';');

    return result[0].substr(0,rc);
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

