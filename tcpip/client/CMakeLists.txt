cmake_minimum_required(VERSION 3.12)
project(client)

set(CMAKE_CXX_STANDARD 17)

add_executable(client
        main.cpp client.cpp ClientConfig.cpp ClientConfig.h Client.cpp Client.h)

target_link_libraries( client pthread )