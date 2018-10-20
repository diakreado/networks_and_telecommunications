#include "SimpleNumbers.h"

SimpleNumbers* SimpleNumbers::instance;

SimpleNumbers::SimpleNumbers() {
    fs = new FileStorage(Config::FILE_PATH);
    vrt = new std::vector<ResultOfTask>();
    maxSimpleNum = 0;
    nextHop = 0;
}

SimpleNumbers::~SimpleNumbers() {
    delete fs;
    delete vrt;
    delete instance;
}

SimpleNumbers* SimpleNumbers::getInstance() {
    if (instance == 0) {
        instance = new SimpleNumbers();
    }
    return instance;
}

void SimpleNumbers::saveNumber(const int id, const long simpleNumber) {
    auto newRecord = std::to_string(simpleNumber) + "|";

//    auto buffer = std::vector<long>();
//    auto rs = new ResultOfTask(id, false, buffer);
//    vrt->push_back(*rs);

    if (simpleNumber > maxSimpleNum) {
        maxSimpleNum = simpleNumber;
    }
    fs->write(newRecord);
}

long SimpleNumbers::getMax() const {
    return maxSimpleNum;
}

std::vector<long> SimpleNumbers::getLast(int n) {
    auto fileData = fs->read();
    std::vector<std::string> formattedData;
    split(fileData, formattedData, '|');

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

void SimpleNumbers::split(const std::string str, std::vector<std::string> &cont, const char divider) {
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, divider)) {
        cont.push_back(token);
    }
}

RangeStructure SimpleNumbers::getRange() {
    std::pair<long, long> range(Config::HOP * nextHop, Config::HOP * (nextHop + 1));
    RangeStructure rs(nextHop, range);
    nextHop++;

    return rs;
}





