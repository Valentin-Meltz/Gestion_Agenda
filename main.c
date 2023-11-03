#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "module timer-20231031/timer.h"
#include "s_d_list.h"

int main() {
    t_list mylist = Create_list(10);

    Add_cell(&mylist, 29, 5);
    Add_cell(&mylist, 56, 3);
    Add_cell(&mylist, 3, 4);
    Add_cell(&mylist, 56, 1);
    Add_cell(&mylist, 40, 3);
    Add_cell(&mylist, 10, 2);
    Add_cell(&mylist, 17, 5);
    Add_cell(&mylist, 35, 9);
    Add_cell(&mylist, 29, 8);
    Add_cell(&mylist, 16, 7);

    Display_All_list_aligne(mylist);
    printf("\n");

    FILE *log_file = fopen("log.txt","w");
    char format[] = "%d\t%s\t%s\n" ;
    int level = 10;
    char *time_lvl0;
    char *time_all_levels;

    startTimer();
    p_cell Cell = search_classic(mylist, 29);
    stopTimer();
    time_lvl0 = getTimeAsString(); // fonction du module timer

    startTimer();
    p_cell cell = search(mylist, mylist.head[mylist.max_level -1], mylist.tail[mylist.max_level -1], 29, mylist.max_level-1);
    stopTimer();
    time_all_levels = getTimeAsString(); // fonction du module timer

    fprintf(log_file,format,level,time_lvl0, time_all_levels);
    fclose(log_file);

    return 0;
}
