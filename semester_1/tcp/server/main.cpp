#include "../Config.h"
#include "Server.h"

#include "model/SimpleNumbers.h"

int main()
{
    auto server = new Server();
    server->start();

    return 0;
}
