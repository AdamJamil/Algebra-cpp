cmake_minimum_required(VERSION 3.17)
project(Algebra)

set(CMAKE_CXX_STANDARD 20)

add_executable(Algebra main.cpp group.h element.h definitions.h definitions.cpp set.h function.h homomorphism.h)