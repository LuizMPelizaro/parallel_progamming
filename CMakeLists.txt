cmake_minimum_required(VERSION 3.18)
project(parallel_programming)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mconsole")


add_executable(parallel_programming
        main.cpp
        exemple/handle_join_example/thread_guard.h
        exemple/handle_join_example/handle_join.h
        exemple/join_threads.h
        exemple/join_threads.h
        exemple/join_and_detach.h
        exemple/initial_exampel_thread.h)
