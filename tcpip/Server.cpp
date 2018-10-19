#include "Server.h"

int Server::acceptSocket;
std::mutex Server::mtx;
std::vector<int> Server::arrayOfConnection;

Server::Server() {
    struct sockaddr_in local {
            AF_INET,
            htons(Config::PORT),
            htonl(INADDR_ANY)
    };

    acceptSocket = socket(AF_INET, SOCK_STREAM, 0);
    bind(acceptSocket, (struct sockaddr *)&local, sizeof(local));
    listen(acceptSocket, 5);
}

void Server::start() {
    auto threadData = (pthrData*) malloc(sizeof(pthrData));

    std::thread acceptThr(acceptThread, threadData);

    auto ch = new ConsoleHandler();

    while (true) {
        threadData->action = (char)getchar();

        if (threadData->action == 'i') {
            printf("info\n");
            printf("Number of connections: %d\n", (int)arrayOfConnection.size());
            for (int i = 0; i < arrayOfConnection.size(); i++) {
                printf("%d. client socket: %d\n", i + 1, arrayOfConnection[i]);
            }
        }
        else if (threadData->action == 'e') {
            printf("exit\n");
            break;
        }
        else if (threadData->action == 'h') {
            printf("i -- info\n"
                   "e -- exit\n");
        }
        else if (threadData->action == 'c') {
            printf("close connection: enter number of client\n");
            int client_number = -1;
            scanf("%d", &client_number);

            printf("client_number  %d\n", client_number - 1);

            shutdown(arrayOfConnection[client_number - 1], SHUT_RDWR);
            close(arrayOfConnection[client_number - 1]);

            printf("socket %d closed \n", arrayOfConnection[client_number - 1]);
        }
    }

    shutdown(acceptSocket, SHUT_RDWR);
    close(acceptSocket);

    acceptThr.join();

    delete ch;

    free(threadData);
}

void Server::acceptThread(pthrData* data) {
    int client_socket;

    while (true) {
        if (data->action == 'e') {
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

    for (int i = 0; i < arrayOfConnection.size(); i++) {
        shutdown(arrayOfConnection[i], SHUT_RDWR);
        close(arrayOfConnection[i]);
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
            printf("result is null\n");
        }
        else {
            printf("%d : %s\n", s1, result);
        }
    }

    mtx.lock();
    arrayOfConnection.erase(std::remove(arrayOfConnection.begin(), arrayOfConnection.end(), s1), arrayOfConnection.end());
    mtx.unlock();
}