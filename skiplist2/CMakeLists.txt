#CMake 最低版本号要求
cmake_minimum_required (VERSION 2.6)

# 项目信息
project (skiplist)

#设置
SET(CMAKE_CXX_FLAGS "-std=c++0x")

# 指定生成目标
add_executable(skiplist main.cpp)

