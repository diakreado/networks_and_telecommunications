#include "SimpleNumbers.h"

SimpleNumbers* SimpleNumbers::instance;
std::mutex SimpleNumbers::mtx;

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

    std::vector<long> outputData;

    for (std::string strNum : formattedData) {
        outputData.push_back(std::stol(strNum));
    }

    outputData.push_back(simpleNumber);

    std::sort(outputData.begin(), outputData.end());

    std::stringstream ss;
    for (long longNum : outputData) {
        ss << longNum << "|";
    }

    mtx.lock();
    numberStorage->write(ss.str());
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
    auto nextHop = std::stoi(hopStorage->read());
    std::pair<long, long> range(Config::HOP * nextHop, Config::HOP * (nextHop + 1));
    nextHop++;
    hopStorage->write(std::to_string(nextHop));
    mtx.unlock();

    return range;
}





