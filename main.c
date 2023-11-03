#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "s_d_list.h"

int main() {
    t_list mylist = Create_list(10);

    Add_cell(&mylist, 29, 5);
    Add_cell(&mylist, 56, 3);
    Add_cell(&mylist, 56, 1);
    Add_cell(&mylist, 40, 3);
    Add_cell(&mylist, 10, 2);
    Add_cell(&mylist, 17, 5);
    Add_cell(&mylist, 35, 9);
    Add_cell(&mylist, 29, 8);
    Add_cell(&mylist, 16, 7);

    Display_All_list(mylist);
    printf("\n");
    Display_All_list_aligne(mylist);
    printf("\n");

    t_list mylist_2 = Create_list(3);
    int* levels = Create_levels(mylist_2);
    Add_levels(&mylist_2, levels);
    Display_All_list_aligne(mylist_2);
    printf("\n");

    printf("%d ", strcmp("fran", "toto"));

    return 0;
}
