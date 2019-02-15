
#include "RequestHandler.h"
#include "Server.h"

SimpleNumbers* RequestHandler::model = SimpleNumbers::getInstance();

void RequestHandler::handle(struct sockaddr_in si_other, std::string request) {
    std::vector<std::string> partOfRequest;
    Utility::split(request, partOfRequest, '?');

    if (partOfRequest.size() < 2) {
        Server::write(si_other, "400|");
    } else {
        std::string command = partOfRequest[0];
        if (command == "TEST") {
            Server::write(si_other, "TEST_C");

        } else if (command == "MAX") {
            Server::write(si_other, "200| " + std::to_string(model->getMax()));

        } else if (command == "LAST") {
            std::stringstream ss;
            auto last = model->getLast(std::stoi(partOfRequest[1]));
            ss << "200| ";
            for (long num : last) {
                ss << num << ",";
            }
            Server::write(si_other, ss.str());
        } else if (command == "FROM") {
            auto range = model->getRange();
            Server::write(si_other, "200| " + std::to_string(range.first) + "," + std::to_string(range.second));
        } else if (command == "POST") {
            model->saveNumber(std::stoi(partOfRequest[1]));
            Server::write(si_other, "200| ");
        } else {
            Server::write(si_other, "400| ");
        }
    }
}
