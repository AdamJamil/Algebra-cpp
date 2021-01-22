cmake_minimum_required(VERSION 3.17)
project(Algebra)

set(CMAKE_CXX_STANDARD 14)

add_executable(Algebra main.cpp group.cpp group.h element.cpp element.h)