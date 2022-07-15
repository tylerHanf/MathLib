cmake_minimum_required(VERSION 3.10)
project(Mathlib
        VERSION 0.1
        LANGUAGES CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib/)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

if (NOT TARGET Logger)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/Logger)
endif()

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SOURCE)

add_library(Mathlib ${SOURCE})

target_include_directories(Mathlib
    PRIVATE
    "$<TARGET_PROPERTY:Logger,INTERFACE_INCLUDE_DIRECTORIES"
)       

target_link_libraries(Mathlib Logger)