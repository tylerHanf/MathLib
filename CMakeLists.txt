cmake_minimum_required(VERSION 3.10)
project(TMathlib
        VERSION 0.1
        LANGUAGES C CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib/)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SOURCE)

add_library(TMathlib ${SOURCE})
target_include_directories(TMathlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(TMathlib PUBLIC Logger)
target_link_libraries(TMathlib Logger)
