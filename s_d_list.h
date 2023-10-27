#ifndef GESTION_AGENDA_S_D_LIST_H
#define GESTION_AGENDA_S_D_LIST_H

//Structure d'une cellule à level niveau
struct s_d_cell {
    int value;
    int level;
    struct s_d_cell **next;     //Liste de tous les pointeurs next de chaque niveau
};
typedef struct s_d_cell t_cell, *p_cell;

p_cell Create_cell(int, int);   //Création d'une cellule
void Display_cell(p_cell);  //affichage d'une cellule


//Structure d'une list à max_level niveau maximum
struct s_d_list {
    int max_level;
    t_cell **head;      //Liste de tous les pointeurs head de chaque niveau
};
typedef struct s_d_list t_list;

t_list Create_list(int);    //Création d'une liste vide

void Add_Head_list(t_list*, int, int);    //Ajout d'une cellule en tête de list
void Add_cell_level(t_list*, p_cell, int); // Ajout d'une cellule par odre croissant sur un niveau donner
void Add_cell(t_list*, int val, int level);     //Ajout d'une cellule à niveau en respectant l'ordre croissant

int isEmptyList(t_list, int);
int IsValinList(t_list, int);   //Test si une valeur est situé dans la liste
int NbCell(t_list, int);
int NbBetweenCell(p_cell, p_cell);
int NbBetweenHead(t_list, p_cell);

void Display_level_aligne(t_list, int);
void Display_list_level(t_list, int);    //Affichage d'un niveau de la liste
void Display_All_list(t_list);    //Affichage de tous les niveaux de la liste
void Display_All_list_aligne(t_list);   //Affichage de tous les niveau de la liste (aligné)

//Test git push

#endif //GESTION_AGENDA_S_D_LIST_H