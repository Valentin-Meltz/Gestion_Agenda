#include <stdio.h>
#include <stdlib.h>
#include "s_d_list.h"

p_cell Create_cell(int level, int val){
    p_cell cell = (p_cell) malloc(sizeof(p_cell));
    cell->level = level;
    cell->value = val;
    cell->next = (p_cell *) malloc(cell->level * sizeof(p_cell));
    for (int i = 0; i < cell->level; i++){
        cell->next[i] = NULL;
    }
    return cell;
}

void Display_cell(p_cell cell){
    printf("[ %d|@-]", cell->value);
}

t_list Create_list(int max_level){
    t_list mylist;
    mylist.max_level = max_level;
    mylist.head = (p_cell *) malloc(mylist.max_level * sizeof(p_cell));
    for (int i = 0; i < mylist.max_level; i++){
        mylist.head[i] = NULL;
    }
    return mylist;
}

void Add_Head_list(t_list*, p_cell){

}

void Display_list_level(t_list mylist, int level){
    printf("[list head_%d @-]-->", level);
    if (mylist.head[level] == NULL){
        printf("NULL\n");
        return;
    }

    p_cell temp = mylist.head[level];
    while(temp != NULL){
        Display_cell(temp);
        temp = temp->next[level];
    }
    printf("NULL\n");
}

void Display_All_list(t_list mylist, int level){
    if (level != mylist.max_level)
        Display_list_level(mylist, level++);
}

void Display_All_list_aligne(t_list);
void Add_cell(t_list*, p_cell);