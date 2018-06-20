cmake_minimum_required(VERSION 3.0)
project(mapp)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(libuv)

option(ARGS_BUILD_EXAMPLE "Build example" OFF)
option(ARGS_BUILD_UNITTESTS "Build unittests" OFF)
add_subdirectory(vendor/args)

include_directories(include)
add_subdirectory(src)

add_subdirectory(example)