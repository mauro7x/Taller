cmake_minimum_required(VERSION 2.8)

project(cmake-demo)

add_executable(ej1 main.cpp)
add_subdirectory(classes)

target_link_libraries(ej1 myclasses)
