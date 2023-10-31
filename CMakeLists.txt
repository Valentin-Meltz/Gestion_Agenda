cmake_minimum_required(VERSION 3.24)
project(Gestion_Agenda C)

set(CMAKE_C_STANDARD 11)

add_executable(Gestion_Agenda
        main.c
        s_d_list.c
        s_d_list.h
        contact.c
        contact.h
        rendez-vous.c
        rendez-vous.h
        "module timer-20231031/timer.c"
)
