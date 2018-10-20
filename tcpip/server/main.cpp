#include "Config.h"
#include "Server.h"

#include "FileStorage.h"

int main()
{
    auto server = new Server();
    server->start();

//    auto fs = new FileStorage(Config::FILE_PATH);
//
//    fs->write("polka1231");
//    std::cout << fs->read() << std::endl;

    return 0;
}
