cmake_minimum_required(VERSION 3.21)
project(metro)

set(CMAKE_CXX_STANDARD 17)

add_executable(metro main.cpp Station.cpp Station.h Branch.cpp Branch.h StationList.cpp StationList.h)
