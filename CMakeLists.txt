cmake_minimum_required(VERSION 3.17)
project(SorteVisualization)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
include_directories( ${SDL2_INCLUDE_DIR} )

add_executable(SorteVisualization main.cpp Screen.cpp Sorted.cpp)

target_link_libraries(SorteVisualization ${SDL2_LIBRARY} )