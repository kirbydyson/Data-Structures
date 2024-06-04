cmake_minimum_required(VERSION 3.27)
project(Project6_NetworkBroadcasting)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static")

add_executable(Project6_NetworkBroadcasting
        arrayheap-prof-proj6.h
        arrayheap-student-proj6.h
        graph-proj6.h
        graph-proj6.cpp
        driver-proj6.cpp)
