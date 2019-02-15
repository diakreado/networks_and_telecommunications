#include "SimpleNumbers.h"

SimpleNumbers* SimpleNumbers::instance;
std::mutex SimpleNumbers::mtx;

struct classcomp {
    bool operator() (const long& lhs, const long& rhs) const
    {return lhs<rhs;}
};

SimpleNumbers::SimpleNumbers() {
    numberStorage = new FileStorage(std::string(Config::FILE_PATH) + "data");
    hopStorage = new FileStorage(std::string(Config::FILE_PATH) + "hop");
}

SimpleNumbers::~SimpleNumbers() {
    delete numberStorage;
    delete hopStorage;
    delete instance;
}

SimpleNumbers* SimpleNumbers::getInstance() {
    if (instance == 0) {
        instance = new SimpleNumbers();
    }
    return instance;
}

void SimpleNumbers::saveNumber(const long simpleNumber) {
    auto newRecord = std::to_string(simpleNumber) + "|";

    mtx.lock();
    auto fileData = numberStorage->read();
    mtx.unlock();

    std::vector<std::string> formattedData;
    Utility::split(fileData, formattedData, '|');

    std::set<long,classcomp> outputData;

    for (std::string strNum : formattedData) {
        outputData.insert(std::stol(strNum));
    }

    outputData.insert(simpleNumber);


    std::stringstream ss;
    for (long longNum : outputData) {
        ss << longNum << "|";
    }

    mtx.lock();
    numberStorage->write(ss.str());         // записали число

    auto hopStorageData = hopStorage->read();
    mtx.unlock();
    std::vector<std::string> formattedHopStorageData;
    Utility::split(hopStorageData, formattedHopStorageData, '|');

    std::string substr1;
    std::string substr2;
    if (!formattedHopStorageData.empty()) {
        substr1 = formattedHopStorageData[0];
        if (formattedHopStorageData.size() > 1) {
            substr2 = formattedHopStorageData[1];
        }
    }

    std::vector<std::string> wasCounted;
    Utility::split(substr1, wasCounted, ',');                  // записали, что дипазон отработан

    std::set<long,classcomp> wasCountedData;

    for (std::string strNum : wasCounted) {
        wasCountedData.insert(std::stoi(strNum));
    }
    long range = simpleNumber / Config::HOP;
    wasCountedData.insert(range);

    std::stringstream ssHop;
    for (auto longNum : wasCountedData) {
        ssHop << longNum << ",";
    }
    ssHop << "|" << substr2;

    mtx.lock();
    hopStorage->write(ssHop.str());
    mtx.unlock();
}

long SimpleNumbers::getMax() {
    auto simpNums = getLast(1);
    if (!simpNums.empty()) {
        return simpNums[0];
    } else {
        return 0;
    }
}

std::vector<long> SimpleNumbers::getLast(int n) {
    mtx.lock();
    auto fileData = numberStorage->read();
    mtx.unlock();

    std::vector<std::string> formattedData;
    Utility::split(fileData, formattedData, '|');

    std::vector<long> outputData;

    int size = (int) formattedData.size();
    if (n < 0) {
        n = 0;
    } else if (n > size) {
        n = size;
    }

    for (int i = size - n; i < size ; i++) {
        outputData.push_back(std::stol(formattedData[i]));
    }
    return outputData;
}

std::pair<long, long> SimpleNumbers::getRange() {
    mtx.lock();
    auto fileData = hopStorage->read();
    mtx.unlock();

    std::vector<std::string> formattedData;
    Utility::split(fileData, formattedData, '|');

    std::string substr1;
    std::string substr2;
    if (!formattedData.empty()) {
        substr1 = formattedData[0];
        if (formattedData.size() > 1) {
            substr2 = formattedData[1];
        }
    }

    std::vector<std::string> wasCounted;
    std::vector<std::string> inCounting;

    Utility::split(substr1, wasCounted, ',');
    Utility::split(substr2, inCounting, ',');

    int firstVal = 0;
    int lastVal = 0;
    if (!inCounting.empty()) {
        firstVal = std::stoi(inCounting[0]);
        lastVal = std::stoi(inCounting[inCounting.size() - 1]);
    }
    if (lastVal - firstVal > Config::APPROXIMATE_NUMBER_OF_CLIENTS + 3) {
        inCounting.erase(inCounting.begin());
    }

    std::set<int,classcomp> outputData;

    for (std::string strNum : wasCounted) {
        outputData.insert(std::stoi(strNum));
    }
    for (std::string strNum : inCounting) {
        outputData.insert(std::stoi(strNum));
    }

    std::vector<int> dataVector(outputData.size());
    std::copy(outputData.begin(), outputData.end(), dataVector.begin());

    auto nextHop = getMinMissingNumber(dataVector);
    std::pair<long, long> range(Config::HOP * nextHop, Config::HOP * (nextHop + 1));

    std::stringstream ss;
    for (auto longNum : wasCounted) {
        ss << longNum << ",";
        outputData.erase(std::stoi(longNum));
    }
    ss << "|";
    for (auto longNum : outputData) {
        ss << longNum << ",";
    }
    ss << nextHop << ",";

    mtx.lock();
    hopStorage->write(ss.str());
    mtx.unlock();

    return range;
}

int SimpleNumbers::getMinMissingNumber(const std::vector<int> &arr) {
    for (int j = 0; j < arr.size(); ++j) {
        if (std::find(arr.begin(), arr.end(), j) == arr.end() ) {
            return j;
        }
    }
    if (!arr.empty()) {
        return arr[arr.size()-1] + 1;
    } else {
        return 0;
    }
}
