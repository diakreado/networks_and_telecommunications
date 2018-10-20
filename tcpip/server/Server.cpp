#include "Server.h"

int Server::acceptSocket;
std::mutex Server::mtx;
std::vector<int> Server::arrayOfConnection;
ConsoleHandler Server::ch;

Server::Server() {
    struct sockaddr_in local {
            AF_INET,
            htons(Config::PORT),
            htonl(INADDR_ANY)
    };
    acceptSocket = socket(AF_INET, SOCK_STREAM, 0);
    bind(acceptSocket, (struct sockaddr *)&local, sizeof(local));
    listen(acceptSocket, 5);

    std::cout << "+----------------------------------------+" << std::endl;
    std::cout << "¦  Server binding to port : " << Config::PORT << "         ¦"<< std::endl;
    std::cout << "+----------------------------------------+" << std::endl;
}

int Server::start() {
    std::thread acceptThr(acceptThread);

    ch.startReading();

    shutdown(acceptSocket, SHUT_RDWR);
    close(acceptSocket);

    acceptThr.join();

    return 0;
}

void Server::acceptThread() {
    int client_socket;
    while (true) {
        if (ch.getCommand() == "exit" or ch.getCommand() == "e") {
            break;
        }
        if (arrayOfConnection.size() < Config::NUMBER_OF_CLIENTS) {
            client_socket = accept(acceptSocket, nullptr, nullptr);
            if (client_socket < 0) {
                break;
            }
            new std::thread(threadFunc, &client_socket);

            mtx.lock();
            arrayOfConnection.push_back(client_socket);
            mtx.unlock();
        }
    }

    for (int connection : arrayOfConnection) {
        shutdown(connection, SHUT_RDWR);
        close(connection);
    }
}

int Server::read_n(int n, int s1, char *result) {
    char buf[1];
    int number_of_entered = 0;
    ssize_t rc = -1;

    while (number_of_entered != n) {
        rc = recv(s1, buf, 1, 0);
        if (rc == -1) {
            break;
        }
        result[number_of_entered] = buf[0];
        number_of_entered += rc;
    }
    return (int)rc;
}

void Server::threadFunc(int* data) {
    int s1 = *data;
    char result[Config::NUMBER_OF_READ_SYMBOLS];
    int rc = -1;

    while (true) {
        rc = read_n(Config::NUMBER_OF_READ_SYMBOLS, s1, result);
        if (rc == -1) {
            break;
        }
        std::string res(result);
        if (res.empty()) {
            std::cout << "\n" << "result is null" << std::endl;
            ch.newInputLine();
        }
        else {
            std::cout << "\n" << s1 << " : " << std::endl;
            ch.newInputLine();
        }
    }

    mtx.lock();
    arrayOfConnection.erase(std::remove(arrayOfConnection.begin(), arrayOfConnection.end(), s1), arrayOfConnection.end());
    mtx.unlock();
}

std::vector<int> Server::getArrayOfConnection() {
    return arrayOfConnection;
}