cmake_minimum_required(VERSION 3.5)
project(MyBind)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES main.cpp bind.h)
add_executable(MyBind ${SOURCE_FILES})