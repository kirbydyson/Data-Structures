cmake_minimum_required(VERSION 3.27)
project(Project1_Maze)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static")

add_executable(Project1_Maze
        location-proj1.h
        maze-proj1.h
        stack-proj1.h
        driver-proj1.cpp
        stack-proj1.cpp
        maze-proj1.cpp
        location-proj1.cpp)
