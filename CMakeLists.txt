cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(mpl)

add_library(mpl STATIC
    src/include/mpl/cons.h

    src/test/cons.cpp
)

target_include_directories(mpl
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include
)
