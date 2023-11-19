#ifndef GESTION_AGENDA_CONTACT_H
#define GESTION_AGENDA_CONTACT_H

#include "rendez-vous.h"

char *scanString();

struct contact {
    char* name;
    l_rdv rdv;
    int level;
    struct contact **next;
};
typedef struct contact t_contact, *p_contact;

p_contact Create_contact(char*);
void Display_contact(p_contact);

struct list_contact {
    int max_level;
    t_contact **head;      //Liste de tous les pointeurs head de chaque niveau
    t_contact **tail;      //Liste de tous les pointeurs tail de chaque niveau
};
typedef struct list_contact l_contact;

l_contact CreateL_contact();

void Add_Head_Contact(l_contact*, p_contact, int);  //Ajout d'un contact par la tête
void Add_Tail_Contact(l_contact*, p_contact, int);  //Ajout d'un contact par la queue
void Add_contact(l_contact*, p_contact);    //Ajout d'un contact
void Maj_contact(l_contact*, p_contact);    //Mise à jour du niveau d'un contact

int isEmptyContact(l_contact, int);     //Détermine si la liste est vide ou non
int calculContactLevel(l_contact, p_contact);   //Calcul le nievau auxquel doit être ajouté un contact
void deleteContactLevel(l_contact*, p_contact);     //Supprime un contact


void DisplayAllContact(l_contact);
p_contact SearchClassique_contact(l_contact, char*);
p_contact Search_contact(l_contact, char*);
void Save_contact(l_contact);
void Load_contact(l_contact*);
#endif //GESTION_AGENDA_CONTACT_H