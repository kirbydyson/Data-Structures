cmake_minimum_required(VERSION 3.27)
project(Project5_OS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static")

add_executable(Project5_OS
        arrayheap-prof-proj5.h
        arrayheap-student-proj5.h
        process-proj5.h
        driver-proj5.cpp
        process-proj5.cpp)
