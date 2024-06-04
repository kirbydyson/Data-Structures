cmake_minimum_required(VERSION 3.27)
project(Project2_WordMelt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static")

add_executable(Project2_WordMelt
        maze-proj2.h
        location-proj2.h
        arrayqueue-student-proj2.h
        arrayqueue-prof-proj2.h
        location-proj2.cpp
        maze-proj2.cpp
        driver-proj2.cpp)
