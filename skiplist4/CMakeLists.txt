#cmake版本
cmake_minimum_required(VERSION 2.6)

#项目
project(skiplist)

#设置
SET( CMAKE_CXX_FLAGS "-std=c++11 -O3")

#生成
add_executable(skiplist main.cpp skiplist.h skipnode.h)
