
#include "Client.h"

int main()
{
    auto client = new Client();
    if (client->openConnection() < 0) {
        return -1;
    }

    while (true) {
        std::cout << ">_";
        std::string input;
        std::cin >> input;
        if (input == "next") {
            std::string request = "FROM?;";
            client->write(request);
            auto serverAnswer = client->read();

            std::cout << "serverAnswer : " << serverAnswer << std::endl;

            std::vector<std::string> partsOfAnswer;
            Utility::split(serverAnswer, partsOfAnswer, ' ');

            std::vector<std::string> strNum;
            Utility::split(partsOfAnswer[1], strNum, ',');
            auto answer = client->countSimpleNumbers(std::pair(std::stoi(strNum[0]),std::stoi(strNum[1])));
            request = "POST?";
            for (long num : answer) {
                client->write(request + std::to_string(num) + ";");
                client->read();
            }
        }
        if (input == "max") {
            std::string request = "MAX?;";
            client->write(request);
            auto serverAnswer = client->read();
            std::cout << "serverAnswer : " << serverAnswer << std::endl;
        }
        if (input == "last") {
            std::string request = "LAST?";
            int i;
            std::cin >> i;
            std::cout << std::endl;
            request += std::to_string(i);
            client->write(request);
            auto serverAnswer = client->read();
            std::cout << "serverAnswer : " << serverAnswer << std::endl;
        }
        if (input == "exit") {
            client->closeConnection();
            break;
        }
    }

    return 0;
}
