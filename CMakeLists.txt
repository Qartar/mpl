cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(mpl)

add_library(mpl INTERFACE)

target_include_directories(mpl
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include
)

if(${CMAKE_CXX_COMPILER_ID} STREQUAL GNU OR ${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
    target_compile_options(mpl
        INTERFACE
            -fno-operator-names
    )
endif()

add_library(mpl_test STATIC
    src/include/mpl/cons.h
    src/include/mpl/functional.h
    src/include/mpl/list.h
    src/include/mpl/logical.h
    src/include/mpl/set.h
    src/include/mpl/units.h

    src/test/mpl_test.h
    src/test/cons.cpp
    src/test/functional.cpp
    src/test/list.cpp
    src/test/logical.cpp
    src/test/set.cpp
    src/test/units.cpp

    src/sample/units/physics.cpp
    src/sample/units/physics.h
    src/sample/units/types.h
)

target_link_libraries(mpl_test mpl)
