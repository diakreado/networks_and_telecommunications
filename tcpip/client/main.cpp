
#include "Client.h"

int main()
{
    auto client = new Client();
    if (client->openConnection() < 0) {
        return 1;
    }
    std::string request = "MIX?;";
    client->write(request);
    std::cout << client->read() << std:: endl;

//    request = "LAST?10;";
//    client->write(request);
//    std::cout << client->read() << std:: endl;
//
//    request = "FROM?;";
//    client->write(request);
//    std::cout << client->read() << std:: endl;

//    request = "POST?13;";
//    client->write(request);
//    std::cout << client->read() << std:: endl;

    client->closeConnection();

    return 0;
}
