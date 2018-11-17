
//#include "Client.h"
//
//int main()
//{
//    auto client = new Client();
//    if (client->openConnection() < 0) {
//        return -1;
//    }
//
//    while (true) {
//        std::cout << ">_";
//        std::string input;
//        std::cin >> input;
//        if (input == "next") {
//            std::string request = "FROM?;";
//            client->write(request);
//            auto serverAnswer = client->read();
//
//            std::cout << "serverAnswer : " << serverAnswer << std::endl;
//
//            std::vector<std::string> partsOfAnswer;
//            Utility::split(serverAnswer, partsOfAnswer, ' ');
//
//            std::vector<std::string> strNum;
//            Utility::split(partsOfAnswer[1], strNum, ',');
//            auto answer = client->countSimpleNumbers(std::pair(std::stoi(strNum[0]),std::stoi(strNum[1])));
//            request = "POST?";
//            for (long num : answer) {
//                client->write(request + std::to_string(num) + ";");
//                client->read();
//            }
//        }
//        if (input == "max") {
//            std::string request = "MAX?;";
//            client->write(request);
//            auto serverAnswer = client->read();
//            std::cout << "serverAnswer : " << serverAnswer << std::endl;
//        }
//        if (input == "last") {
//            std::string request = "LAST?";
//            int i;
//            std::cin >> i;
//            std::cout << std::endl;
//            request += std::to_string(i);
//            client->write(request);
//            auto serverAnswer = client->read();
//            std::cout << "serverAnswer : " << serverAnswer << std::endl;
//        }
//        if (input == "exit") {
//            client->closeConnection();
//            break;
//        }
//    }
//
//    return 0;
//}


// Client side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "../Config.h"

// Driver code
int main() {
    int sockfd;
    char buffer[Config::NUMBER_OF_READ_SYMBOLS];
    char *hello = "Hello from client";
    struct sockaddr_in     servaddr;

    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(Config::PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    int n;
    socklen_t len;

    sendto(sockfd, (const char *)hello, strlen(hello),
           MSG_CONFIRM, (const struct sockaddr *) &servaddr,
           sizeof(servaddr));
    printf("Hello message sent.\n");

    n = recvfrom(sockfd, (char *)buffer, Config::NUMBER_OF_READ_SYMBOLS,
                 MSG_WAITALL, (struct sockaddr *) &servaddr,
                 &len);
    buffer[n] = '\0';
    printf("Server : %s\n", buffer);

    close(sockfd);
    return 0;
}

