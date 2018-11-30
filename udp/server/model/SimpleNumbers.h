#ifndef TCPIP_SIMPLENUMBERS_H
#define TCPIP_SIMPLENUMBERS_H

#include <vector>
#include <sstream>
#include <mutex>
#include "FileStorage.h"
#include "../../Config.h"
#include "../../Utility.h"
#include <set>
#include <algorithm>

class SimpleNumbers {

public:
    ~SimpleNumbers();

    static SimpleNumbers* getInstance();

    void saveNumber(long simpleNumber);
    long getMax();
    std::vector<long> getLast(int n);
    std::pair<long, long> getRange();

private:
    SimpleNumbers();

    static int getMinMissingNumber(const std::vector<int> &arr);

    static std::mutex mtx;
    static SimpleNumbers* instance;
    const FileStorage* numberStorage;
    const FileStorage* hopStorage;
};


#endif //TCPIP_MODEL_H
