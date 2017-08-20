# CMake file for building the unit tests

cmake_minimum_required (VERSION 2.8)
project(CD4017-Test)

add_definitions(-std=gnu++0x)
add_definitions(-DUNIT_TEST)
add_executable(CD4017-Test ../main.cpp)