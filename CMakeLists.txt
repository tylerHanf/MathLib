cmake_minimum_required(VERSION 3.10)
project(RMathlib
        VERSION 0.1
        LANGUAGES C CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib/)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SOURCE)

add_library(RMathlib ${SOURCE})
target_include_directories(RMathlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
