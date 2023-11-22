cmake_minimum_required(VERSION 3.24)
project(Gestion_Agenda)

set(CMAKE_C_STANDARD 11)

add_executable(Gestion_Agenda
        contact.c
        main.c
        rendez-vous.c
        s_d_list.c
        "module timer-20231031/timer.c"
)
