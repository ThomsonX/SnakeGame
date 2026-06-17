cmake_minimum_required(VERSION 3.14)
project(Snake)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(thirdparty/raylib)
add_subdirectory(thirdparty/raygui/projects/CMake)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE include/)
target_link_libraries(${PROJECT_NAME} raylib raygui)
