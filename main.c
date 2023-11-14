#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "module timer-20231031/timer.h"
#include "s_d_list.h"
#include "contact.h"
#include "rendez-vous.h"

int main() {
    /*
    FILE *log_file = fopen("log.txt","w");
    int level = 7;
    const char *time_lvl0;
    const char *time_all_levels;

    t_list mylist = Create_list(level);
    int *levels = Create_levels(mylist);
    Add_levels(&mylist, levels);

    Add_cell(&mylist, 5, 6);
    Add_cell(&mylist, 7, 1);
    Add_cell(&mylist, 18, 6);
    Add_cell(&mylist, 5, 2);
    Add_cell(&mylist, 27, 4);
    Add_cell(&mylist, 32, 5);
    Add_cell(&mylist, 64, 3);
    Add_cell(&mylist, 56, 3);

    Display_All_list_aligne(mylist);

    int val = 32;

    for (int i = 0; i < 10; i++) {;
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
    */


    FILE *test_file = fopen("test.txt","w");
    char format[] = "%d/%d/%d %d,%d %d,%d %s\t";

    int day = 0, mounth = 0, year = 0, hour = 0, min = 0, dur_h = 0, dur_m = 0;
    char *object = (char*) malloc(1000 * sizeof(char));
    fscanf(test_file, format, &day, &mounth, &year, &hour, &min, &dur_h, &dur_m, &object);
    printf("%d/%d/%d %d,%d %d,%d %s\t", day, mounth, year, hour, min, dur_h, dur_m, object);

    fclose(test_file);

    return 0;
}