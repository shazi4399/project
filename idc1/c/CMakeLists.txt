cmake_minimum_required(VERSION 3.16)
project(weather)

set(CMAKE_CXX_STANDARD 11)

set(SRC_LIST crtsurfdata3.cpp)
include_directories(../../public)
#aux_source_directory()
message(STATUS "This is BINARY dir" ${weather_BINARY_DIR})
message(STATUS "This is SOURCE dir" ${weather_SOURCE_DIR})

add_executable(weather crtsurfdata3.cpp ../../public/_public.cpp)
