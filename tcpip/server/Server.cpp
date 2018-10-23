
#include "Server.h"


int Server::acceptSocket;
std::mutex Server::mtx;
std::vector<int> Server::arrayOfConnection;
ConsoleHandler Server::consoleH;
RequestHandler Server::requestH;


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
    consoleH.startReading();

    shutdown(acceptSocket, SHUT_RDWR);
    close(acceptSocket);
    acceptThr.join();

    return 0;
}

void Server::acceptThread() {
    int client_socket;
    while (true) {
        if (consoleH.getCommand() == "exit" or consoleH.getCommand() == "e") {
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

void Server::threadFunc(int* data) {
    int s1 = *data;
    char result[Config::NUMBER_OF_READ_SYMBOLS];
    int rc = -1;

    while (true) {
        rc = Utility::read_n(s1, result);
        if (rc == -1) {
            break;
        }
        auto res = std::string(result);
        if (res == "EXIT?") {
            closeConnection(s1);
            break;
        }
        RequestHandler::handle(s1, res);
    }
    mtx.lock();
    arrayOfConnection.erase(std::remove(arrayOfConnection.begin(), arrayOfConnection.end(), s1), arrayOfConnection.end());
    mtx.unlock();
}

std::vector<int> Server::getArrayOfConnection() {
    return arrayOfConnection;
}

void Server::write(const int clientSocket, std::string data) {
    data.push_back(Config::DELIMITER);
    send(clientSocket, data.c_str(), data.size() + 1, 0);
}

void Server::closeConnection(int socket) {
    shutdown(socket, SHUT_RDWR);
    close(socket);
}
