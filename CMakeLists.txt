cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
project(tetris LANGUAGES CXX)

include(CTest)

add_subdirectory(src)
if (BUILD_TESTING)
    add_subdirectory(test)
endif ()