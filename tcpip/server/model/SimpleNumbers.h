#ifndef TCPIP_SIMPLENUMBERS_H
#define TCPIP_SIMPLENUMBERS_H

#include <vector>
#include <sstream>
#include <queue>
#include <algorithm>
#include "FileStorage.h"
#include "../Config.h"

class SimpleNumbers {

public:
    ~SimpleNumbers();

    static SimpleNumbers* getInstance();

    void saveNumber(long simpleNumber);
    long getMax() const;
    std::vector<long> getLast(int n);
    std::pair<long, long> getRange();

    static void split(std::string str, std::vector<std::string>& cont, char divider);

private:
    SimpleNumbers();

    static SimpleNumbers* instance;

    long maxSimpleNum;
    int nextHop;

    const FileStorage* fs;
};


#endif //TCPIP_MODEL_H
