#include "ConsoleHandler.h"
#include "Server.h"

void ConsoleHandler::startReading() {
    while (true) {
        newInputLine();
        std::cin >> command;

        auto connections = Server::getArrayOfConnection();

        if (command == "info" or command == "i") {
            std::cout << "Number of connection : " << connections.size() << std::endl;
            for (int i = 0; i < connections.size(); i++) {
                std::cout << i + 1 << ". client socket: " << connections[i] << std::endl;
            }
        }
        else if (command == "exit" or command == "e") {
            std::cout << "Shutdown server." << std::endl;
            break;
        }
        else if (command == "help" or command == "h") {
            std::cout << "i - info" << std::endl;
            std::cout << "h - help" << std::endl;
            std::cout << "c - close" << std::endl;
            std::cout << "clear" << std::endl;
            std::cout << "e - exit" << std::endl;
        } 
        else if (command == "clear") {
            for (int i = 0; i < 10; ++i) {
                std::cout << std::endl;
            }
        }
        else if (command == "close" or command == "c") {
            if (connections.empty()) {
                std::cout << "No open connections" << std::endl;
            } else {
                std::cout << "Close connection." << std::endl;
                for (int i = 0; i < connections.size(); i++) {
                    std::cout << "    " << i + 1 << ". client socket: " << connections[i] << std::endl;
                }
                std::cout << "Enter number of close connection : ";

                int client_number = -1;
                std::cin >>  client_number;

                shutdown(connections[client_number - 1], SHUT_RDWR);
                close(connections[client_number - 1]);

                std::cout << "Socket " << connections[client_number - 1] << " closed" << std::endl;
            }
        } else {
            std::cout << command << ": command not found" << std::endl;
        }
    }
}

void ConsoleHandler::newInputLine() {
    std::cout << "server_> ";
}

std::string ConsoleHandler::getCommand() {
    return command;
}
