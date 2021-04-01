cmake_minimum_required(VERSION 3.17)
project(Algebra)

set(CMAKE_CXX_STANDARD 20)

add_executable(Algebra main.cpp group.h element.cpp element.h definitions.h set.h function.h function.cpp)