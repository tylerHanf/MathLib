cmake_minimum_required(VERSION 3.10)
project(Mathlib
        VERSION 0.1
        LANGUAGES CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib/)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SOURCE)

add_library(Mathlib ${SOURCE})