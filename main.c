#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "module timer-20231031/timer.h"
#include "s_d_list.h"

int main() {
    FILE *log_file = fopen("log.txt","w");
    int level = 7;
    char *time_lvl0;
    char *time_all_levels;

    t_list mylist = Create_list(level);
    int* levels = Create_levels(mylist);
    Add_levels (&mylist, levels);

    for (int i = 0; i < 10; i++) {
        int val = rand() % 120;

        startTimer();
        p_cell Cell = search_classic(mylist, val);
        stopTimer();
        time_lvl0 = getTimeAsString(); // fonction du module timer

        startTimer();
        p_cell cell = search(mylist, mylist.head[mylist.max_level - 1], mylist.tail[mylist.max_level - 1], val, mylist.max_level - 1);
        stopTimer();
        time_all_levels = getTimeAsString(); // fonction du module timer

        fprintf(log_file, "%d\t%s\t%s\n", level, time_lvl0, time_all_levels);
    }

    fclose(log_file);
    return 0;
}