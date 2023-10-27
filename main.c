#include <stdio.h>
#include <stdlib.h>
#include "s_d_list.h"

int main() {
    t_list mylist = Create_list(10);

    Add_cell(&mylist, 29, 5);
    Add_cell(&mylist, 12, 3);
    Add_cell(&mylist, 56, 1);
    Add_cell(&mylist, 40, 3);
    Add_cell(&mylist, 10, 2);
    Add_cell(&mylist, 17, 7);
    Add_cell(&mylist, 35, 9);
    Add_cell(&mylist, 29, 8);
    Add_cell(&mylist, 16, 5);

    Display_All_list(mylist);
    printf("\n");
    Display_All_list_aligne(mylist);
    return 0;
}
