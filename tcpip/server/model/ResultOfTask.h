#ifndef TCPIP_RESULTOFTASK_H
#define TCPIP_RESULTOFTASK_H

#include <vector>

class ResultOfTask {

public:
    ResultOfTask(int id, bool performed, std::vector<long> bufferOfTask){
        this->id = id;
        this->performed = performed;
        this->bufferOfTask = bufferOfTask;
    }

    int id;
    bool performed;
    std::vector<long> bufferOfTask;
};

#endif //TCPIP_BUFFER_H
