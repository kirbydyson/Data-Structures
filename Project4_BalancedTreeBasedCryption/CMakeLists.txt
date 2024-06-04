cmake_minimum_required(VERSION 3.27)
project(Project4_BalancedTreeBasedCryption)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static")

add_executable(Project4_BalancedTreeBasedCryption
        avl-tree-prof-proj4.h
        avl-tree-student-proj4.h
        driver-proj4.cpp)
