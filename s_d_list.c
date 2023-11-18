#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "s_d_list.h"
#include "module timer-20231031/timer.h"

static int cptRecherche = 0;

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
        if(cell->value >= 1000)
            printf("[%d|@-]", cell->value);
        else if(cell->value >= 100)
            printf("[ %d|@-]", cell->value);
        else if(cell->value >= 10)
            printf("[  %d|@-]", cell->value);
        else
            printf("[   %d|@-]", cell->value);
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
                printf("------------");
            }
            printf("-->");
            Display_cell(temp);
            while (temp->next[level] != NULL) {
                cpt = NbBetweenCell(temp, temp->next[level]);   //On calcule le nombre de cellule entre la temp et et son succésseur dans la liste de niveau 0
                for (int i = 0; i < cpt; i++) {
                    printf("------------");
                }
                printf("-->");
                Display_cell(temp->next[level]);
                temp = temp->next[level];
            }
            cpt = NbBetweenCell(temp, NULL);    //On calcule le nombre de cellule entre la queur et NULL dans la liste de niveau 0
        }
        for (int i = 0; i < cpt; i++) {
            printf("------------");
        }
        printf("-->NULL\n");
    }
}


//Partie 2
int* Create_levels(t_list mylist){
    int *levels = (int *) calloc((int)(pow(2, mylist.max_level)-1), sizeof(int));
    for(int i = 0; i < mylist.max_level; i++){
        for(int j = (int)(pow(2, i)-1); j < (int)(pow(2, mylist.max_level)-1); j += (int)(pow(2, i))){
            levels[j]++ ;
        }
    }
    return levels;
}
void Add_levels(t_list* mylist, int *levels){
    for(int i = 0; i < (int)(pow(2, mylist->max_level)-1); i++){
        Add_cell(mylist, i+1, levels[i]);
    }
}

p_cell search_classic (t_list mylist, int val){     //Mettre compteur de recherche
    p_cell cur = mylist.head[0];
    while (cur != NULL && cur->value != val){
        cptRecherche++;
        cur = cur->next[0];
    }
    return cur;
}
p_cell search (t_list myList, int val){
    int level = myList.max_level - 1;
    while(isEmptyList(myList, level)){
        level --;
    }

    p_cell startCell = myList.head[level], endCell = myList.tail[level];
    while(level != -1) {
        // Si start est la bonne cell
        if(startCell->value == val) return startCell;
        cptRecherche ++;

        // Si end est la bonne cell
        if(endCell->value == val) return endCell;
        cptRecherche ++;

        // On recherche au millieu
        // Si start est supérieur à val
        if(startCell->value > val) startCell = myList.head[level - 1];

            // Si Start est inférieur à val
        else if (endCell->value < val) endCell = myList.tail[level -1];

            // Si val est entre les bornes
        else {
            p_cell cur = startCell, prev = cur;
            while (cur->value <= val) {
                // Si on trouve la valeur
                if (cur->value == val) return cur;

                cptRecherche ++;
                prev = cur;
                cur = cur->next[level];
            }
            // On change les bornes
            startCell = prev;
            endCell = cur;
        }
        level --; // On décrémente le niveau
    }
    return NULL;
}

void createTxtComplexite(){
    FILE *log_file = fopen("log.txt","w");
    char format[] = "%d\t%d\t%s |%d|\t%s |%d|\n", *time_lvl0, *time_all_levels;
    int cptlvl0, cpt_all_levels, val;
    p_cell searchCell;

    for(int i = 7; i < 15; i++) {
        t_list mylist = Create_list(i);
        int *levels = Create_levels(mylist);
        Add_levels(&mylist, levels);

        val = (rand() % (mylist.tail[0]->value - 0 + 1)) + 0;   //vérifier la fonction rand jusqu'ou est si cela renvoie bien des entier

        startTimer();
        searchCell = search_classic(mylist, val);
        stopTimer();
        time_lvl0 = getTimeAsString(); // fonction du module timer
        cptlvl0 = cptRecherche;
        cptRecherche = 0;

        startTimer();
        searchCell = search(mylist, val);
        stopTimer();
        time_all_levels = getTimeAsString();
        cpt_all_levels = cptRecherche;
        cptRecherche = 0;

        fprintf(log_file, format, val, mylist.max_level, time_lvl0, cptlvl0, time_all_levels, cpt_all_levels);
    }

    fclose(log_file);
}