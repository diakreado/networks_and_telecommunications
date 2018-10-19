#include "Config.h"
#include "Server.h"

int main()
{
    auto server = new Server();
    server->start();

    return 0;
}
