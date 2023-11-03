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

t_contact Create_contact(char*);     //Paul
void Display_contact(p_contact);    //Tuan

struct list_contact {
    int max_level;
    t_contact **head;      //Liste de tous les pointeurs head de chaque niveau
    t_contact **tail;      //Liste de tous les pointeurs tail de chaque niveau
};
typedef struct list_contact l_contact;

l_contact CreateL_contact();    //Paul
int isEmptyContact(l_contact, int);
int IsAddLevel(l_contact , p_contact, int);
void Add_Head_Contact(l_contact*, p_contact, int);
void Add_Tail_Contact(l_contact*, p_contact, int);
void Add_contact(l_contact*, p_contact);    //Valentin


void DisplayL_contact(l_contact);   //Tuan
void Delete_contact(l_contact*, char*);     //Valentin
p_contact Search_contact(l_contact);    //Valentin
void Save_contact();  //Pas fini    //Valentin
void Load_contact();  //Pas fini ca retournera la liste dans lequels sont stocké les contact    //Valentin

#endif //GESTION_AGENDA_CONTACT_H