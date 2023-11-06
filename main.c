#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "module timer-20231031/timer.h"
#include "s_d_list.h"
#include "contact.h"

int main() {
    FILE *log_file = fopen("log.txt","w");
    char format[] = "%d\t%s\t%s\n" ;
    int level = 7;
    char *time_lvl0;
    char *time_all_levels;

    t_list mylist = Create_list(level);
    int* levels = Create_levels(mylist);
    Add_levels (&mylist, levels);

    for(int i = 0; i < 10; i++) {
        startTimer();
        p_cell Cell = search_classic(mylist, rand() % 120);
        stopTimer();
        time_lvl0 = getTimeAsString(); // fonction du module timer

        startTimer();
        p_cell cell = search(mylist, mylist.head[mylist.max_level - 1], mylist.tail[mylist.max_level - 1], rand() % 120, mylist.max_level - 1);
        stopTimer();
        time_all_levels = getTimeAsString(); // fonction du module timer

        fprintf(log_file, format, level, time_lvl0, time_all_levels);
    }

    fclose(log_file);

    return 0;
}