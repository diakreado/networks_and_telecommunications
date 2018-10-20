#ifndef TCPIP_RANGESTRUCTURE_H
#define TCPIP_RANGESTRUCTURE_H

#include <utility>

class RangeStructure {

public:

    RangeStructure(int id, std::pair<long, long> range) {
        this->id = id;
        this->range = range;
    }

    int id;
    std::pair<long, long> range;
};

#endif //TCPIP_RANGESTRUCTURE_H
