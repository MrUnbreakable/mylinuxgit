cmake_minimum_required(VERSION 2.8)

project(test)
set(CMAKE_CXX_FLAGS " -g -std=c++11 ${CMAKE_CXX_FLAGS}")
link_directories(/temp/lib64)
include_directories(src)
add_executable(test ./src/test.cpp)
target_link_libraries(test fmt)
