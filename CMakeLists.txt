cmake_minimum_required(VERSION 3.22)
project(GetPassWord)

set(CMAKE_CXX_STANDARD 17)

add_executable(GetPassWord Tool.h Info.h InfoManager.h Socket.h client.cpp)
