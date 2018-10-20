#ifndef SERVER_FILESTORAGE_H
#define SERVER_FILESTORAGE_H

#include <iostream>
#include <fstream>

class FileStorage {

public:
    explicit FileStorage(std::string fileName);
    ~FileStorage();

    void write(std::string  inputData);
    std::string read();

private:
    const std::string* fileName;
};


#endif //SERVER_FILESTORAGE_H
