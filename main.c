#include <stdio.h>
#include <stdlib.h>
#include "s_d_list.h"

int main() {
    printf("Hello, World!\n\n");

    t_list mylist = Create_list(9);

    Add_cell(&mylist, 29, 5);
    Add_cell(&mylist, 12, 7);
    Add_cell(&mylist, 56, 1);
    Add_cell(&mylist, 40, 3);
    Add_cell(&mylist, 10, 2);
    Add_cell(&mylist, 16, 7);
    Add_cell(&mylist, 16, 5);

    Display_All_list(mylist);
    printf("\n");
    Display_level_aligne(mylist, 1);
    return 0;
}
