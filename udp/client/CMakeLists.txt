cmake_minimum_required(VERSION 3.12)
project(client)

set(CMAKE_CXX_STANDARD 17)

add_executable(client
        main.cpp Client.cpp Client.h
        ../Utility.cpp ../Utility.h ../Config.h ../Config.cpp)

target_link_libraries( client pthread )