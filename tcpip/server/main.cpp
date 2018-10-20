#include "Config.h"
#include "Server.h"

#include "model/SimpleNumbers.h"

int main()
{
    auto server = new Server();
//    server->start();

    auto model = SimpleNumbers::getInstance();

    auto data = model->getLast(10);
    for (long strNum : data) {
        std::cout << strNum;
    }
    std::cout << std::endl;

    return 0;
}
