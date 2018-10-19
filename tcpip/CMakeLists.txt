cmake_minimum_required(VERSION 3.5)
project(server)

set(CMAKE_CXX_STANDARD 17)

add_executable(server
        main.cpp ConsoleHandler.cpp ConsoleHandler.h Config.h Server.cpp Server.h)

target_link_libraries( server pthread )