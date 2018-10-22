
#include "RequestHandler.h"
#include "Server.h"

SimpleNumbers* RequestHandler::model = SimpleNumbers::getInstance();

void RequestHandler::handle(int socket, std::string request) {
    std::vector<std::string> partOfRequest;
    Utility::split(request, partOfRequest, '?');

    if (partOfRequest.size() < 2) {
        Server::write(socket, "400|");
        return;
    }

    std::string command = partOfRequest[0];
    if (command == "MAX") {
        Server::write(socket, "200| " + std::to_string(model->getMax()));

    } else if (command == "LAST") {
        std::stringstream ss;
        auto last = model->getLast(std::stoi(partOfRequest[1]));
        ss << "200| ";
        for (long num : last) {
            ss << num << ",";
        }
        Server::write(socket, ss.str());
    } else if (command == "FROM") {

        Server::write(socket, "200| ");
    } else if (command == "POST") {
        model->saveNumber(std::stoi(partOfRequest[1]));
        Server::write(socket, "200| ");
    } else {
        Server::write(socket, "400| ");
        return;
    }
}
