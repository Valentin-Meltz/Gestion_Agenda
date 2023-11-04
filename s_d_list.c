#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "s_d_list.h"

//Fonction d'affichage
int GetNbChiffre(int n){
    if(n <= 0) return 0;
    return 1 + GetNbChiffre(n/10);
}

//Partie 1
p_cell Create_cell(int level, int val){
    p_cell cell = (p_cell) malloc(sizeof(p_cell));      //Création de la cellule
    cell->level = level;        //Attribution des valeurs
    cell->value = val;
    cell->next = (p_cell *) malloc(cell->level * sizeof(p_cell));   //Allocution dynamique d'un tableau de pointeur (**p_cell)
    for (int i = 0; i < cell->level; i++){      //Mise à NULL de tous les champs next dans le tableau
        cell->next[i] = NULL;
    }
    return cell;
}
void Display_cell(p_cell cell){
    if(cell == NULL) printf("NULL");
    else {
        switch (GetNbChiffre(cell->value)) {     //Affichage d'une cellule en fonction du nombre de chiffre de sa valeur
            case 1:
                printf("[  %d|@-]", cell->value);
                break;
            case 2:
                printf("[ %d|@-]", cell->value);
                break;
            default:
                printf("[%d|@-]", cell->value);
        }
    }
}

t_list Create_list(int max_level) {
    t_list mylist;      //Création de la cellule
    mylist.max_level = max_level;   //Attribution de la valeur max_level
    mylist.head = (p_cell *) malloc(mylist.max_level * sizeof(p_cell));     //Allocution dynamique d'un tableau de pointeur (**p_cell)
    mylist.tail = (p_cell *) malloc(mylist.max_level * sizeof(p_cell));     //Allocution dynamique d'un tableau de pointeur (**p_cell)
    for (int i = 0; i < mylist.max_level; i++){     //Mise à NULL de tous les champs head et tail dans les tableaux
        mylist.head[i] = NULL;
        mylist.tail[i] = NULL;
    }
    return mylist;
}

int isEmptyList(t_list mylist, int level){
    return mylist.head[level] == NULL && mylist.tail[level] == NULL;    //return 1 si une liste est vide | 0 si elle n'est pas vide
}
int NbBetweenHead(t_list mylist, p_cell cell){
    if(mylist.head[0] == cell) return 0;
    return NbBetweenCell(mylist.head[0], cell) + 1;     //return le nombre de cellule entre la tête d'une liste et la cellule en paramètre
}
int NbBetweenCell(p_cell cell1, p_cell cell2){
    if(cell1 == cell2) return 0;
    p_cell temp1 = cell1;
    int nbCell = 0;
    while (temp1->next[0] != cell2){        //Calcul le nombre de cellule entre les cellules données en paramètre
        nbCell ++;
        temp1 = temp1->next[0];
    }
    return nbCell;
}

void Add_Head_list(t_list* mylist, p_cell newcell, int level){
    if (isEmptyList(*mylist, level)){       //Ajout d'une cellule à la tête
        mylist->head[level] = newcell;
        mylist->tail[level] = newcell;
        return;
    }
    newcell->next[level] = mylist->head[level];
    mylist->head[level] = newcell;
}
void Add_Tail_List(t_list* mylist, p_cell newcell, int level){
    if (isEmptyList(*mylist, level)){   //Ajout de la cellule à la queue
        mylist->head[level] = newcell;
        mylist->tail[level] = newcell;
        return;
    }
    mylist->tail[level]->next[level] = newcell;
    mylist->tail[level] = newcell;
}
void Add_cell(t_list* mylist, int val, int level){
    p_cell newcell = Create_cell(level, val);
    for(level = 0; level < newcell->level; level++){    //Boucle parcourant tous les niveaux de la liste auquelle doit être ajouté la nouvelle cellule
        if (isEmptyList(*mylist, level) || mylist->head[level]->value >= newcell->value)    //Si la liste est vide ou que la valeur de la cellule tête est inférieur à la nouvelle cellule on ajoute à la tête
            Add_Head_list(mylist, newcell, level);
        else if (mylist->tail[level]->value < newcell->value)   //Si la valeur de la nouvelle cellule est supérieur à la valeur de la cellule queue on ajoute à la queue
            Add_Tail_List(mylist, newcell, level);
        else{
            p_cell temp = mylist->head[level], prev = temp;
            while (temp != NULL) {      //On parcours la liste jusqu'a trouvé le bonne endroit on ajouté la nouvelle cellule
                if (newcell->value > prev->value && newcell->value <= temp->value) {    //On ajoute la jouvelle cellule
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
    printf("[list head_%d @-]-->", level);  //On affiche l'entête de la liste
    p_cell temp = mylist.head[level];
    while(temp != NULL){    //On parcours la liste et on affiche chaque cellule
        Display_cell(temp);
        printf("-->");
        temp = temp->next[level];
    }
    printf("NULL\n");
}
void Display_All_list(t_list mylist){
    for(int i = 0; i < mylist.max_level; i++){  //On parcours tous les niveau de liste pour afficher chaque niveau
        Display_list_level(mylist, i);
    }
}
void Display_All_list_aligne(t_list mylist){
    Display_list_level(mylist, 0);  //On affiche le niveau 0
    for (int level =1; level < mylist.max_level; level++){  //On parcours tous les niveau de la liste
        printf("[list head_%d @-]", level);
        int cpt;
        if (mylist.head[level] == NULL) cpt = NbBetweenHead(mylist, NULL);
        else {
            p_cell temp = mylist.head[level];
            cpt = NbBetweenHead(mylist, mylist.head[level]);    //On calcule le nombre de cellule entre la tête et la première cellule du niveau dans la liste de niveau 0
            for (int i = 0; i < cpt; i++) {
                printf("-----------");
            }
            printf("-->");
            Display_cell(temp);
            while (temp->next[level] != NULL) {
                cpt = NbBetweenCell(temp, temp->next[level]);   //On calcule le nombre de cellule entre la temp et et son succésseur dans la liste de niveau 0
                for (int i = 0; i < cpt; i++) {
                    printf("-----------");
                }
                printf("-->");
                Display_cell(temp->next[level]);
                temp = temp->next[level];
            }
            cpt = NbBetweenCell(temp, NULL);    //On calcule le nombre de cellule entre la queur et NULL dans la liste de niveau 0
        }
        for (int i = 0; i < cpt; i++) {
            printf("-----------");
        }
        printf("-->NULL\n");
    }
}

p_cell search_classic (t_list mylist, int val){
    p_cell cur = mylist.head[0];
    while (cur != NULL && cur->value != val){
        cur = cur->next[0];
    }
    return cur;
}

p_cell search (t_list mylist, p_cell start, p_cell end, int val, int level){
    if(level == 0) {
        return search_classic(mylist, val);
    }
    if(isEmptyList(mylist, level)) {
        return search(mylist, mylist.head[level - 1], mylist.tail[level - 1], val, level - 1);
    }
    if(start->value == val) return start;
    if(end->value == val) return end;
    if(start == end && start->value > val) return search(mylist, mylist.head[level-1], start, val, level-1);
    if(start == end && start->value < val) return search(mylist, start, mylist.tail[level-1], val, level-1);
    p_cell cur = start, prev = cur;
    while (cur != end){
        if (cur->value == val) return cur;
        if (cur->value > val){
            return search(mylist, prev, cur, val, level-1);
        }
        prev = cur;
        cur = cur->next[level];
    }
    return search(mylist, prev, end, val, level-1);
}


//Partie 2
int* Create_levels(t_list mylist){
    int *levels = (int *) calloc(pow(2, mylist.max_level)-1, sizeof(int));
    for(int i = 0; i < mylist.max_level; i++){
        for(int j = pow(2, i)-1; j < pow(2, mylist.max_level)-1; j += pow(2, i)){
            levels[j]++ ;
        }
    }
    return levels;
}
void Add_levels(t_list* mylist, int *levels){
    for(int i = 0; i < pow(2, mylist->max_level)-1; i++){
        Add_cell(mylist, i+1, levels[i]);
    }
}