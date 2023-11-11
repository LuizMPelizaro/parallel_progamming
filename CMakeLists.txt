cmake_minimum_required(VERSION 3.18)
project(parallel_programming)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mconsole")


add_executable(parallel_programming
        exercises/exercise_1.cpp)
