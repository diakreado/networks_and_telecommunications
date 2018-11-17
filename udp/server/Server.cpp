
#include "Server.h"


int Server::server_socket;
std::string Server::command;


Server::Server() {
    struct sockaddr_in si_me;

    memset((char *) &si_me, 0, sizeof(si_me));

    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(Config::PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);

    server_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (server_socket < 0) {
        error_message("socket");
    }

    int b = bind(server_socket, (struct sockaddr *) &si_me, sizeof(si_me));
    if (b < 0) {
        error_message("bind");
    }

    std::cout << "+----------------------------------------+" << std::endl;
    std::cout << "¦  UDP server binding to port : " << Config::PORT << "         ¦"<< std::endl;
    std::cout << "+----------------------------------------+" << std::endl;
}

int Server::start() {
    std::thread acceptThr(mainThread);

    while (true) {
        std::string in;
        std::cin >> in;

        if (in == "exit" or in == "e") {
            command = in;
            break;
        }
        else {
            std::cout << "command not found" << std::endl;
        }
    }

    closeConnection(server_socket);
    acceptThr.join();

    return 0;
}

void Server::mainThread() {

    struct sockaddr_in si_other;

    char buffer[Config::NUMBER_OF_READ_SYMBOLS];
    socklen_t slen = sizeof(si_other);
    ssize_t recv_len;

    while (true) {
        if (command == "exit" or command == "e") {
            break;
        }

        std::cout << "Waiting for data...";
        fflush(stdout);

        recv_len = recvfrom(server_socket, buffer, Config::NUMBER_OF_READ_SYMBOLS, 0, (struct sockaddr *) &si_other, &slen);
        if (recv_len == -1) {
            error_message("recvfrom()");
        }
        new std::thread(threadFunc, si_other, buffer);
    }
}

void Server::threadFunc(struct sockaddr_in si_other, std::string data) {

    std::cout << "Received packet from " << inet_ntoa(si_other.sin_addr) << ":" << ntohs(si_other.sin_port) << std::endl;
    std::cout << "Data: " << data << std::endl;

    RequestHandler::handle(si_other, data);
}

void Server::write(const sockaddr_in si_other, std::string data) {
    data.push_back(Config::DELIMITER);

    socklen_t slen = sizeof(si_other);

    if (sendto(server_socket, data.c_str(), data.size(), 0, (struct sockaddr*) &si_other, slen) == -1) {
        error_message("sendto()");
    }
}

void Server::closeConnection(int socket) {
    shutdown(socket, SHUT_RDWR);
    close(socket);
}

void Server::error_message(char* s) {
    perror(s);
    exit(1);
}

