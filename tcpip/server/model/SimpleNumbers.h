#ifndef TCPIP_SIMPLENUMBERS_H
#define TCPIP_SIMPLENUMBERS_H

#include <vector>
#include <sstream>
#include <queue>
#include "FileStorage.h"
#include "RangeStructure.h"
#include "../Config.h"
#include "ResultOfTask.h"

class SimpleNumbers {

public:
    ~SimpleNumbers();

    static SimpleNumbers* getInstance();

    void saveNumber(int id, long simpleNumber);
    long getMax() const;
    std::vector<long> getLast(int n);
    RangeStructure getRange();

    static void split(std::string str, std::vector<std::string>& cont, char divider);

private:
    SimpleNumbers();

    static SimpleNumbers* instance;

    long maxSimpleNum;
    int nextHop;

    std::vector<ResultOfTask>* vrt;

    const FileStorage* fs;
};


#endif //TCPIP_MODEL_H
