cmake_minimum_required(VERSION 3.14)
project(Snake)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(thirdparty/raylib)
add_subdirectory(thirdparty/raygui/projects/CMake)

add_executable(main src/main.cpp)
target_include_directories(main PRIVATE include/)
target_link_libraries(main raylib raygui)
