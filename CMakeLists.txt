cmake_minimum_required(VERSION 3.0.0)
project(tetris LANGUAGES CXX)

include(CTest)

add_subdirectory(src)
if(BUILD_TESTING)
    add_subdirectory(test)
endif()