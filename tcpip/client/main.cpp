
#include <thread>
#include "Client.h"

int clientShouldWork() {
    auto client = new Client();
    if (client->openConnection() < 0) {
        return 1;
    }

    std::cout << "FROM request" << std::endl;

    std::string request = "FROM?;";
    client->write(request);
    auto serverAnswer = client->read();

    std::cout << "serverAnswer : " << serverAnswer << std::endl;

    std::vector<std::string> partsOfAnswer;
    Utility::split(serverAnswer, partsOfAnswer, ' ');

    std::vector<std::string> strNum;
    Utility::split(partsOfAnswer[1], strNum, ',');
    auto answer = client->countSimpleNumbers(std::pair(std::stoi(strNum[0]),std::stoi(strNum[1])));

    std::cout << "POST request" << std::endl;

    request = "POST?";
    for (long num : answer) {
        client->write(request + std::to_string(num) + ";");
        client->read();
    }

    client->closeConnection();
}

int main()
{
    std::thread clientsThr1(clientShouldWork);
    std::thread clientsThr2(clientShouldWork);

    clientsThr1.join();
    clientsThr2.join();

    return 0;
}
