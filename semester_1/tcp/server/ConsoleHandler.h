#ifndef SERVER_CONSOLEHANDLER_H
#define SERVER_CONSOLEHANDLER_H

#include <iostream>

class ConsoleHandler {

public:
    void startReading();
    std::string getCommand();
    void newInputLine();

private:
    std::string command;
};


#endif //SERVER_CONSOLEHANDLER_H
