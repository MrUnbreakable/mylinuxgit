cmake_minimum_required(VERSION 2.8)
project(luatest)

set(CMAKE_CXX_FLAGS " -g -std=c++11 ${CMAKE_CXX_FLAGS}")

LINK_DIRECTORIES(/home/linux/linux/luatables/lib)
FIND_PACKAGE (Lua51 REQUIRED)

INCLUDE_DIRECTORIES (
        ${LUA_INCLUDE_DIR}
        src/
)

include_directories(../inc)
add_executable(luatest ./src/main.cc)

TARGET_LINK_LIBRARIES (
        luatest 
        luatables
        ${LUA_LIBRARIES}
        )
