cmake_minimum_required(VERSION 3.22)
project(r3_philosophers C)

set(CMAKE_C_STANDARD 11)

include_directories(exemple/42_philosophers/philo/includes)
include_directories(includes)

add_executable(r3_philosophers
        includes/philosophers.h
        includes/utils.h
        src/parsing.c
        src/linked_list.c
        src/main.c
        src/main_utils.c
        src/print.c)
