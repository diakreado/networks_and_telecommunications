cmake_minimum_required(VERSION 3.12)
project(server)

set(CMAKE_CXX_STANDARD 17)

add_executable(server
        main.cpp ConsoleHandler.cpp ConsoleHandler.h
        Config.h Server.cpp Server.h model/FileStorage.cpp
        model/FileStorage.h Config.cpp model/SimpleNumbers.cpp
        model/SimpleNumbers.h model/RangeStructure.h model/ResultOfTask.h RequestHandler.cpp RequestHandler.h)

target_link_libraries( server pthread )