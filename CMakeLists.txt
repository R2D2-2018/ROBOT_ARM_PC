cmake_minimum_required(VERSION 2.6)

project(robot_arm_pc)
set(exe_name "robot_arm_pc")

enable_testing()
include(../../flags.cmake)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(sources
    src/main.cpp)

add_executable(${exe_name} ${sources})
