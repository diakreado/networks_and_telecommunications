
#include "RequestHandler.h"
#include "Server.h"


void RequestHandler::handle(int socket, std::string request) {
    std::vector<std::string> partOfRequest;
    Utility::split(request, partOfRequest, '?');

    int i = 0;
    for (std::string part : partOfRequest) {
        i++;
        std::cout << "part " << i << "  : " << part << " ";
    }
    std::cout << std::endl;

    if (partOfRequest.size() < 2) {
        Server::write(socket, "400|");
    } else {
        Server::write(socket, "200|");
    }
}
