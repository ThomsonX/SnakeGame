cmake_minimum_required(VERSION 3.14)
project(Snake)

add_subdirectory(thirdparty/raylib)

add_executable(main src/main.cpp)
target_link_libraries(main raylib)
