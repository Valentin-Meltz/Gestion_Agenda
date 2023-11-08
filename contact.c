#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "contact.h"
#include "rendez-vous.h"

char* scanString(){
    char *S_name = (char*) malloc(50 * sizeof(char)), *F_name = (char*) malloc(50 * sizeof(char));
    printf("Saisir le nom : ");
    scanf("%s %s", S_name, F_name);

    if (F_name[0] >= 65 && F_name[0] <= 90)
    {
        F_name[0] += 32;
    }
    if (S_name[0] >= 65 && S_name[0] <= 90)
    {
        S_name[0] += 32;
    }

    strcat(F_name, "_");
    strcat(F_name, S_name);
    return F_name;
}

p_contact Create_contact(char* name){
    p_contact mycontact = (p_contact) malloc(sizeof(t_contact));
    mycontact->level = 0;
    mycontact->rdv = NULL;
    for (int i = 0; i < 4 ; i++)
    {
        mycontact->next[i] = NULL;
    }
    strcpy(mycontact->name, name);
    return mycontact;
}

int isEmptyContact(l_contact mylist, int level){
    return mylist.head[level] == NULL && mylist.tail[level] == NULL;
}
int IsAddLevel(l_contact mylist, p_contact newcell, int level){
    p_contact temp = mylist.head[level], prev = temp;
    switch (level) {
        case 3:
            if (isEmptyContact(mylist, 0) || strcmp(newcell->name, temp->name) < 0) return 1;
            if (strcmp(newcell->name, mylist.tail[level]->name) > 0 && newcell->name[0] != mylist.tail[level]->name[0]) return 1;
            while (temp != NULL){
                if(strcmp(newcell->name, prev->name) > 0 && strcmp(newcell->name, temp->name) < 0 && newcell->name[0] != prev->name[0]) return 1;
                prev = temp;
                temp = temp->next[level];
            }
            break;
        case 2:
            if (IsAddLevel(mylist, newcell, 3)) return 1;
            if (strcmp(newcell->name, mylist.tail[level]->name) > 0 && newcell->name[0] == mylist.tail[level]->name[0] && newcell->name[1] != mylist.tail[level]->name[1]) return 1;
            while (temp != NULL){
                if(strcmp(newcell->name, prev->name) > 0 && strcmp(newcell->name, temp->name) < 0 && newcell->name[0] == prev->name[0] && newcell->name[1] != prev->name[1]) return 1;
                prev = temp;
                temp = temp->next[level];
            }
            break;
        case 1:
            if (IsAddLevel(mylist, newcell, 2)) return 1;
            if(strcmp(newcell->name, mylist.tail[level]->name) > 0 && newcell->name[0] == mylist.tail[level]->name[0] && newcell->name[1] == mylist.tail[level]->name[1] && newcell->name[2] != mylist.tail[level]->name[2]) return 1;
            while (temp != NULL){
                if(strcmp(newcell->name, prev->name) > 0 && strcmp(newcell->name, temp->name) < 0 && newcell->name[0] == prev->name[0] && newcell->name[1] == prev->name[1] && newcell->name[2] != prev->name[2]) return 1;
                prev = temp;
                temp = temp->next[level];
            }
            break;
        case 0:
            return 1;
        default:
            break;
    }
    return 0;
}
void Add_Head_Contact(l_contact* mylist, p_contact newcell, int level){
    if (isEmptyContact(*mylist, level)){
        mylist->head[level] = newcell;
        mylist->tail[level] = newcell;
    } else {
        newcell->next[level] = mylist->head[level];
        mylist->head[level] = newcell;
    }
}
void Add_Tail_Contact(l_contact* mylist, p_contact newcell, int level){
    if (isEmptyContact(*mylist, level)){
        mylist->head[level] = newcell;
        mylist->tail[level] = newcell;
    } else {
        mylist->tail[level]->next[level] = newcell;
        mylist->tail[level] = newcell;
    }
}
void Add_contact(l_contact* mylist, p_contact newcell) {
    int newlevel = 1;
    if (IsAddLevel(*mylist, newcell, 3)) newlevel = 4;
    else if (IsAddLevel(*mylist, newcell, 2)) newlevel = 3;
    else if (IsAddLevel(*mylist, newcell, 1)) newlevel = 2;

    if (newcell->level != newlevel) {
        for (int level = newcell->level; level < newlevel; level++) {
            if (isEmptyContact(*mylist, level) || strcmp(newcell->name, mylist->head[level]->name) < 0)    //Si la liste est vide ou que la valeur de la cellule tête est inférieur à la nouvelle cellule on ajoute à la tête
                Add_Head_Contact(mylist, newcell, level);
            else if (strcmp(newcell->name, mylist->tail[level]->name) > 0)   //Si la valeur de la nouvelle cellule est supérieur à la valeur de la cellule queue on ajoute à la queue
                Add_Tail_Contact(mylist, newcell, level);
            else {
                p_contact temp = mylist->head[level], prev = temp;
                while (temp != NULL) {      //On parcours la liste jusqu'a trouvé le bonne endroit on ajouté la nouvelle cellule
                    if (strcmp(newcell->name, prev->name) > 0 && strcmp(newcell->name, temp->name) < 0) {    //On ajoute la jouvelle cellule
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
        newcell->level = newlevel;
        Add_contact(mylist, newcell->next[0]);
    }
}

void Delete_contact(l_contact* mylist, char* name){     //Je laisse ca la mais on va peut etre pas delete les contatcs
    p_contact temp = mylist->head[0], prev = temp;
    if(strcmp(temp->name, name) == 0){
        mylist->head[0] = temp->next[0];
        mylist->head[1] = temp->next[1];
        mylist->head[2] = temp->next[2];
        mylist->head[3] = temp->next[3];
        Add_contact(mylist, mylist->head[0]);
    }
}

void Save_contact(l_contact mylist){
    char formatName[]  = "%s\n", formatRdv[] = "%d/%d/%d %d,%d %d,%d %s\t";
    FILE *stock_contact = fopen("Stock_contact.txt","w");
    FILE *stock_rdv = fopen("Stock_rdv.txt","w");

    p_contact temp = mylist.head[0];
    while (temp != NULL){
        fprintf(stock_contact, formatName, temp->name);
        p_rdv cur = temp->rdv->head;
        while (cur != NULL){
            fprintf(stock_rdv, formatRdv, cur->date->day, cur->date->month, cur->date->year, cur->hour->hour, cur->hour->minute, cur->duration->hour, cur->duration->minute, cur->object);
            cur = cur->next;
        }
        fprintf(stock_rdv, "\n");
        temp = temp->next[0];
    }

    fclose(stock_rdv);
    fclose(stock_contact);
}
/*
void Load_contact(l_contact* mylist){
    char formatName[]  = "%s\n";
    char *name;
    FILE *stock_contact = fopen("Stock_contact.txt","r");
    FILE *stock_rdv = fopen("Stock_rdv.txt","r");

    while(fgets(name, stock_contact) != NULL){

    }
    do{
        fscanf(stock_contact, formatName, &name);
    } while(fscanf(stock_contact, formatName, &name) != NULL);
}
*/