cmake_minimum_required(VERSION 3.12)
project(server)

set(CMAKE_CXX_STANDARD 17)

add_executable(server
        main.cpp
        Server.cpp Server.h model/FileStorage.cpp
        model/FileStorage.h model/SimpleNumbers.cpp
        model/SimpleNumbers.h  RequestHandler.cpp RequestHandler.h
        ../Utility.cpp ../Utility.h ../Config.h ../Config.cpp)

target_link_libraries( server pthread )