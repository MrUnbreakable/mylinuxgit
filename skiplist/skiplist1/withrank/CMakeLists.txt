#CMake最低版本号要求
cmake_minimum_required(VERSION 2.6)

#项目信息
project(SkipList_with_rank)

#指定生成目标
add_executable(SkipList_with_rank skiplist_with_rank_test.c skiplist_with_rank.h)
