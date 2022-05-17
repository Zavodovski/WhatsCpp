cmake_minimum_required(VERSION 3.22.1)

project(WhatsCpp)

include(cmakeconf/building_output.cmake)
include(cmakeconf/compiler_conf.cmake)

add_subdirectory(BasicSTL)
add_subdirectory(Modern-C++)
add_subdirectory(AdvancedC++)
add_subdirectory(AdvancedSTL)
add_subdirectory(ConcurrentProgramming)
