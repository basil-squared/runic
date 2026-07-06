cmake_minimum_required(VERSION 3.10)
project(Runic C)

find_package(Lua REQUIRED)

add_executable(Runic src/main.c
    src/parser.c)
target_include_directories(Runic PRIVATE include)
target_include_directories(Runic PRIVATE ${LUA_INCLUDE_DIR})
target_link_libraries(Runic PRIVATE ${LUA_LIBRARIES})