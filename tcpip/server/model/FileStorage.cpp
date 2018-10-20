#include "FileStorage.h"


FileStorage::FileStorage(const std::string fileName) {
    this->fileName = new std::string(fileName);
}

FileStorage::~FileStorage() {
    delete this->fileName;
}

void FileStorage::write(const std::string inputData) const {
    std::ofstream out(*fileName, std::ios::app);
    if (!out.is_open()) {
        std::cout << "Cannot open file." << std::endl;
        return;
    }
    out << inputData;
    out.close ();
}

std::string FileStorage::read() const {
    std::ifstream in(*fileName);
    std::string fileData;
    if (!in.is_open()) {
        std::cout << "Cannot open file." << std::endl;
        return fileData;
    }
    in >> fileData;
    in.close ();

    return fileData;
}
