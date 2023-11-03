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

    Display_All_list_aligne(mylist);
    printf("\n");

    p_cell cell = search(mylist, mylist.head[mylist.max_level -1], mylist.tail[mylist.max_level -1], 29, mylist.max_level-1);
    if(cell == NULL) printf("NULL ");
    else printf("%d ", cell->value);

    p_cell cell2 = search(mylist, mylist.head[mylist.max_level -1], mylist.tail[mylist.max_level -1], 10, mylist.max_level-1);
    if(cell2 == NULL) printf("NULL ");
    else printf("%d ", cell2->value);

    p_cell cell3 = search(mylist, mylist.head[mylist.max_level -1], mylist.tail[mylist.max_level -1], 71, mylist.max_level-1);
    if(cell3 == NULL) printf("NULL ");
    else printf("%d ", cell3->value);

    p_cell cell4 = search(mylist, mylist.head[mylist.max_level -1], mylist.tail[mylist.max_level -1], 56, mylist.max_level-1);
    if(cell4 == NULL) printf("NULL ");
    else printf("%d ", cell4->value);

    return 0;
}
