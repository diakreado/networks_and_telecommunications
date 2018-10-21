
#include "Client.h"


Client::Client() {
    peer.sin_family = AF_INET;
    peer.sin_port = htons(ClientConfig::PORT);
    peer.sin_addr.s_addr = inet_addr(ClientConfig::INET_ADDR);

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
}

void Client::openConnection() {
    connect(clientSocket, (struct sockaddr *)&peer, sizeof(peer));
    std::cout << "Client connect to " << ClientConfig::INET_ADDR << " " << ClientConfig::PORT << std::endl;
}

void Client::closeConnection() {
    //todo request to server for exit
    
    shutdown(clientSocket, SHUT_RDWR);              
    close(clientSocket);
    std::cout << "Connection is closed" << std::endl;
}


void Client::write(std::string data) {
    send(clientSocket, data.c_str(), 26, 0);
}

std::string Client::read() {
    return "polka";
}

