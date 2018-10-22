#include "SimpleNumbers.h"

SimpleNumbers* SimpleNumbers::instance;

SimpleNumbers::SimpleNumbers() {
    fs = new FileStorage(Config::FILE_PATH);
    maxSimpleNum = 0;
    nextHop = 0;
}

SimpleNumbers::~SimpleNumbers() {
    delete fs;
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

    if (simpleNumber > maxSimpleNum) {
        maxSimpleNum = simpleNumber;
    }

    auto fileData = fs->read();
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

    fs->write(ss.str());
}

long SimpleNumbers::getMax() {
    return getLast(1)[0];
}

std::vector<long> SimpleNumbers::getLast(int n) {
    auto fileData = fs->read();
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
    std::pair<long, long> range(Config::HOP * nextHop, Config::HOP * (nextHop + 1));
    nextHop++;

    return range;
}





