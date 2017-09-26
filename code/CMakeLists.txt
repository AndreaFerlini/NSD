cmake_minimum_required(VERSION 3.8)
project(code)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        graphstats.cpp
        graphstats.h
        main.cpp
        storegaph.cpp
        storegaph.h)

add_executable(code ${SOURCE_FILES})