
#include "Client.h"


Client::Client() {
    peer.sin_family = AF_INET;
    peer.sin_port = htons(Config::PORT);
    peer.sin_addr.s_addr = INADDR_ANY;

    if ( (serverSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
}

void Client::closeConnection() {
    write("EXIT?");
    shutdown(serverSocket, SHUT_RDWR);
    close(serverSocket);
    std::cout << "Connection was closed" << std::endl;
}

void Client::write(std::string data) {
    size_t sizeOfBuffer = (size_t) Config::NUMBER_OF_READ_SYMBOLS;

    sendto(serverSocket, data.c_str(), sizeOfBuffer, MSG_CONFIRM, (const struct sockaddr *) &peer, sizeof(peer));
}

std::string Client::read() {
    char buffer[Config::NUMBER_OF_READ_SYMBOLS];
    ssize_t rc = -1;
    socklen_t slen = sizeof(peer);

    rc = recvfrom(serverSocket, (char *)buffer, Config::NUMBER_OF_READ_SYMBOLS, MSG_CONFIRM, (struct sockaddr *) &peer, &slen);

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

int Client::getServerSocket() {
    return serverSocket;
}

bool isclosed(const int sock) {
    fd_set rfd;
    FD_ZERO(&rfd);
    FD_SET(sock, &rfd);
    timeval tv = { 0 };
    select(sock+1, &rfd, nullptr, nullptr, &tv);
    if (!FD_ISSET(sock, &rfd))
        return false;
    int n = 0;
    ioctl(sock, FIONREAD, &n);
    return n == 0;
}

bool Client::isServerReachable() {
    size_t sizeOfBuffer = (size_t) Config::NUMBER_OF_READ_SYMBOLS;

    std::string data = "TEST?;";
    sendto(serverSocket, data.c_str(), sizeOfBuffer, MSG_CONFIRM, (const struct sockaddr *) &peer, sizeof(peer));

    char buffer[Config::NUMBER_OF_READ_SYMBOLS];
    socklen_t slen = sizeof(peer);


    struct timeval tv;
    tv.tv_sec = 2;
    tv.tv_usec = 0;

    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(serverSocket, &readfds);

    int ret = select(serverSocket+1, &readfds, NULL, NULL, &tv);
    if (ret > 0) {
        // socket has pending data to read
        if (recvfrom(serverSocket, (char *)&buffer, Config::NUMBER_OF_READ_SYMBOLS, MSG_CONFIRM, (struct sockaddr *)&peer, &slen) >= 0)
        {
            // todo: verify the packet is an acknowledgement
            // of the packet sent above and not something else...
            std::cout << "ack received" << std::endl;

            return true;
        }
        else
        {
            std::cout << "error reading" << std::endl;
        }
    }
    else if (ret == 0) {
        std::cout << "timed out waiting for ack" << std::endl;
        // todo: resend the same packet again, or abort the transfer
    } else {
        std::cout << "error selecting" << std::endl;
    }

    return false;

//    recvfrom(serverSocket, (char *)buffer, Config::NUMBER_OF_READ_SYMBOLS, MSG_CONFIRM, (struct sockaddr *) &peer, &slen);


//    std::string strBuff(buffer);

//    return strBuff == "TEST_C;";

//    return
}

