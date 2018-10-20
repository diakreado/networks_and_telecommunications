#ifndef TCPIP_BUFFER_H
#define TCPIP_BUFFER_H

#include <vector>

class ResultsOfTask {

public:

    int id;
    bool performed;
    std::vector<long> bufferOfTask;
};


#endif //TCPIP_BUFFER_H
