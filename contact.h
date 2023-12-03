#ifndef GESTION_AGENDA_CONTACT_H
#define GESTION_AGENDA_CONTACT_H

#include "rendez-vous.h"

//Structure d'un contact
struct contact {
    char* name;
    l_rdv rdv;
    int level;
    struct contact **next;
};
typedef struct contact t_contact, *p_contact;

char *scanString(void);     //Input du nom d'un contact
p_contact Create_contact(char*);    //Création d'un contact
void Display_contact(p_contact);    //Affichage d'un contact

//Structure d'une liste à niveau stockant des contacts
struct list_contact {
    int max_level;
    t_contact **head;      //Liste de tous les pointeurs head de chaque niveau
    t_contact **tail;      //Liste de tous les pointeurs tail de chaque niveau
};
typedef struct list_contact l_contact;

l_contact CreateL_contact(void); //Création d'un liste vide de contact

void Add_Head_Contact(l_contact*, p_contact, int);  //Ajout d'un contact par la tête
void Add_Tail_Contact(l_contact*, p_contact, int);  //Ajout d'un contact par la queue
void Add_contact(l_contact*, p_contact);    //Ajout d'un contact
void Maj_contact(l_contact*, p_contact);    //Mise à jour du niveau d'un contact

int Is_Empty_Contact(l_contact, int);     //Test si la liste est vide ou non
int Calcul_Contact_Level(l_contact, p_contact);   //Calcul du niveau auxquel doit être ajouté un contact

void Display_All_Contact(l_contact);    //Affichage de la liste de contact
p_contact Search_Classique_Contact(l_contact, char*);   //Recherche d'un contact au niveau 0
p_contact Search_Contact(l_contact, char*);     //Recherche d'un contact multi-niveau
p_contact Completion(l_contact myContactList, char* name);

void Save_contact(l_contact);   //Sauvegarde de la liste de contact
void Load_contact(l_contact*);  //Chargement de la liste de contact

void Etude_Complexite_Contact(char*);

#endif //GESTION_AGENDA_CONTACT_H