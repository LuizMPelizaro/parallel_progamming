cmake_minimum_required(VERSION 3.18)
project(parallel_programming)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mconsole")


#add_executable(parallel_programming
#        main.cpp
#        src/exemple/handle_join_example/thread_guard.h
#        src/exemple/handle_join_example/handle_join.h
#        src/exemple/join_threads.h
#        src/exemple/join_threads.h
#        src/exemple/join_and_detach.h
#        src/exemple/initial_exampel_thread.h
#)

add_executable(exercise2
        src/exercises/exercise_2/crew_mebers.h
        src/exercises/exercise_2/crew_mebers.cpp)