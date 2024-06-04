cmake_minimum_required(VERSION 3.27)
project(Project3_TreeBasedEncryption)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static")

add_executable(Project3_TreeBasedEncryption
        bst-prof-proj3.h
        bst-student-proj3.h
        driver-proj3.cpp)
