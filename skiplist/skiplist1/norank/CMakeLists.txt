# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (SkipList)


# 指定生成目标
add_executable(SkipList  skiplist_test.c skiplist.h)
