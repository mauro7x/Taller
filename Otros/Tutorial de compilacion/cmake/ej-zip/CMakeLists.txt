cmake_minimum_required(VERSION 2.8)

project(cmake-demo)

add_executable(ej-zip main.cpp)

target_link_libraries(ej-zip zip)
