cmake_minimum_required (VERSION 2.8)

project (pthread_cond)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
include_directories(./)

add_executable(pthread_cond main.c)
