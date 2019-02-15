cmake_minimum_required(VERSION 3.12)
project(tcpip)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(client)
add_subdirectory(server)

add_custom_target(tcpip)
add_dependencies(tcpip client server)