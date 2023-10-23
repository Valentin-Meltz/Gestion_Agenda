cmake_minimum_required(VERSION 3.26)
project(Gestion_Agenda C)

set(CMAKE_C_STANDARD 11)

add_executable(Gestion_Agenda main.c
        s_d_list.c
        s_d_list.h
        "module timer-20231023/timer.c"
        "module timer-20231023/timer.h"
)
