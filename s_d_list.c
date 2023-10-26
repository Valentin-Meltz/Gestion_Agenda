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
    return;
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

void Add_Head_list(t_list* mylist, int val, int level){
    p_cell newcell = Create_cell(level, val);
    for(int i = 0; i < newcell->level; i++){
        newcell->next[i] = mylist->head[i];
        mylist->head[i] = newcell;
    }
    return;
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
        printf("-->");
        temp = temp->next[level];
    }
    printf("NULL\n");
    return;
}

void Display_All_list(t_list mylist){
    for(int i = 0; i < mylist.max_level; i++){
        Display_list_level(mylist, i);
    }
    return;
}

void Display_level_aligne(t_list mylist, int level){
    Display_list_level(mylist, 0);
    printf("[list head_%d @-]", level);
    p_cell temp_0 = mylist.head[0], temp_level = mylist.head[level];
    while (temp_level != NULL) {
        int nbCell = 0;
        while (temp_0 != NULL) {
            if(temp_level == temp_0) {
                for (int i = 0; i < nbCell; i++) {
                    printf("--------");
                }
                printf("-->");
                Display_cell(temp_level);
                break;
            }
            temp_0 = temp_0->next[0];
            nbCell++;
        }
        temp_level = temp_level->next[level];
        temp_0 = temp_level;
    }
    int nbCell = 0;
    while (temp_0 != NULL) {
        if(temp_level == temp_0) {
            for (int i = 0; i < nbCell; i++) {
                printf("--------");
            }
            printf("-->");
            Display_cell(temp_level);
            break;
        }
        temp_0 = temp_0->next[0];
        nbCell++;
    }
    temp_level = temp_level->next[level];
    temp_0 = temp_level;
}

void Display_All_list_aligne(t_list mylist){
    Display_list_level(mylist, 0);
    for(int j = 1;j < mylist.max_level; j++){
        printf("[list head_%d @-]", j);
        p_cell prev = mylist.head[0];
        p_cell val = mylist.head[j];
        while(prev != NULL){
            if(prev == val){
                printf("-->");
                Display_cell(val);
            }
            else{
                printf("-----------");
            }
            val = val->next[1];
            prev = prev->next[1];
        }
        printf("-->NULL\n");
    }
    printf(">NULL\n");
    return;
}

void Add_cell_level(t_list* mylist, p_cell newcell, int level){
    if (mylist->head[level] == NULL){
        mylist->head[level] = newcell;
        return;
    }
    if (mylist->head[level]->value > newcell->value){
        newcell->next[level] = mylist->head[level];
        mylist->head[level] = newcell;
        return;
    }
    p_cell temp = mylist->head[level], prev = temp;
    while (temp != NULL){
        if(newcell->value > prev->value && newcell->value <= temp->value){
            prev->next[level] = newcell;
            newcell->next[level] = temp;
            return;
        }
        prev = temp;
        temp = temp->next[level];
    }
    prev->next[level] = newcell;
    return;
}

void Add_cell(t_list* mylist, int val, int level){
    p_cell newcell = Create_cell(level, val);
    for(int i = 0; i < newcell->level; i++){
        Add_cell_level(mylist, newcell, i);
    }
    return;
}