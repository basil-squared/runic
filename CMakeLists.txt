cmake_minimum_required(VERSION 3.10)
project(Runic C)

find_package(Lua REQUIRED)

add_executable(Runic src/main.c
    src/parser.c
    src/memoryutils.c
    src/functionhelpers.c)
target_include_directories(Runic PRIVATE include)
target_include_directories(Runic PRIVATE ${LUA_INCLUDE_DIR})
target_link_libraries(Runic PRIVATE ${LUA_LIBRARIES})
target_compile_options(Runic PRIVATE -fsanitize=address -g)
target_link_options(Runic PRIVATE -fsanitize=address)