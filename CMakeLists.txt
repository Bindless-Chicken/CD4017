cmake_minimum_required (VERSION 3.0)
project(CD4017-Unit)

add_definitions(-DUNIT_TEST)
add_executable(CD4017-Unit CD4017/main.cpp)