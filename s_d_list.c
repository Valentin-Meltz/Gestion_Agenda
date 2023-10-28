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
    mylist.tail = (p_cell *) malloc(mylist.max_level * sizeof(p_cell));
    for (int i = 0; i < mylist.max_level; i++){
        mylist.head[i] = NULL;
        mylist.tail[i] = NULL;
    }
    return mylist;
}
int isEmptyList(t_list mylist, int level){
    return mylist.head[level] == NULL && mylist.tail[level] == NULL;
}
int NbBetweenHead(t_list mylist, p_cell cell){
    if(mylist.head[0] == cell) return 0;
    return NbBetweenCell(mylist.head[0], cell) + 1;
}
int NbBetweenCell(p_cell cell1, p_cell cell2){
    if(cell1 == cell2) return 0;
    p_cell temp1 = cell1;
    int nbCell = 0;
    while (temp1->next[0] != cell2){
        nbCell ++;
        temp1 = temp1->next[0];
    }
    return nbCell;
}

void Add_Head_list(t_list* mylist, p_cell newcell, int level){
    if (isEmptyList(*mylist, level)){
        mylist->head[level] = newcell;
        mylist->tail[level] = newcell;
        return;
    }
    newcell->next[level] = mylist->head[level];
    mylist->head[level] = newcell;
}
void Add_Tail_List(t_list* mylist, p_cell newcell, int level){
    if (isEmptyList(*mylist, level)){
        mylist->head[level] = newcell;
        mylist->tail[level] = newcell;
        return;
    }
    mylist->tail[level]->next[level] = newcell;
    mylist->tail[level] = newcell;
}
void Add_cell(t_list* mylist, int val, int level){
    p_cell newcell = Create_cell(level, val);
    for(level = 0; level < newcell->level; level++){
        if (isEmptyList(*mylist, level) || mylist->head[level]->value >= newcell->value)
            Add_Head_list(mylist, newcell, level);
        else if (mylist->tail[level]->value < newcell->value)
            Add_Tail_List(mylist, newcell, level);
        else{
            p_cell temp = mylist->head[level], prev = temp;
            while (temp != NULL) {
                if (newcell->value > prev->value && newcell->value <= temp->value) {
                    prev->next[level] = newcell;
                    newcell->next[level] = temp;
                    break;
                }
                prev = temp;
                temp = temp->next[level];
            }
            prev->next[level] = newcell;
        }
    }
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
}
void Display_All_list(t_list mylist){
    for(int i = 0; i < mylist.max_level; i++){
        Display_list_level(mylist, i);
    }
}
void Display_All_list_aligne(t_list mylist){
    Display_list_level(mylist, 0);
    for (int level =1; level < mylist.max_level; level++){
        printf("[list head_%d @-]", level);
        int cpt;
        if (mylist.head[level] == NULL) cpt = NbBetweenHead(mylist, NULL);
        else {
            p_cell temp = mylist.head[level];
            cpt = NbBetweenHead(mylist, mylist.head[level]);
            for (int i = 0; i < cpt; i++) {
                printf("-----------");
            }
            printf("-->");
            Display_cell(temp);
            while (temp->next[level] != NULL) {
                cpt = NbBetweenCell(temp, temp->next[level]);
                for (int i = 0; i < cpt; i++) {
                    printf("-----------");
                }
                printf("-->");
                Display_cell(temp->next[level]);
                temp = temp->next[level];
            }
            cpt = NbBetweenCell(temp, NULL);
        }
        for (int i = 0; i < cpt; i++) {
            printf("-----------");
        }
        printf("-->NULL\n");
    }
}