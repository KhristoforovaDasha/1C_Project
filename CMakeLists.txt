cmake_minimum_required(VERSION 3.24)
project(1C_Project)

set(CMAKE_CXX_STANDARD 14)

add_executable(1C_Project
        main.cpp src/graph.h src/graph.cpp src/solver.h src/solver.cpp)
