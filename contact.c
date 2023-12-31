#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "contact.h"
#include "rendez-vous.h"

static int cptRecherche = 0;

char* scanString(void) {
    char *name = (char*) malloc(100 * sizeof(char));
    printf("Saisir le nom (Nom Prénom) : ");

    //On saisie le nom
    fgets(name, 100, stdin);

    //On vérifie  si la syntaxe est correcte
    int cpt = 0;
    while(name[cpt] != '\n'){
        //Si il s'agit d'un espace
        if(name[cpt] == ' ')
            name[cpt] = '_';

            //Si il s'agit d'une majuscule
        else if(name[cpt] >= 65 && name[cpt]  <= 90)
            name[cpt] += 32;

        cpt ++;
    }
    name[cpt] = '\0';
    return name;
}

//Fonction relativent au contact
p_contact Create_contact(char* name){
    p_contact mycontact = (p_contact) malloc(sizeof(t_contact));
    mycontact->level = 0;
    mycontact->rdv = Create_L_rdv();
    mycontact->next = (p_contact *) malloc(4 * sizeof(p_contact));
    for (int i = 0; i < 4 ; i++)
    {
        mycontact->next[i] = NULL;
    }
    mycontact->name = (char*) malloc(100 * sizeof(char));
    strcpy(mycontact->name, name);
    return mycontact;
}
void Display_contact(p_contact contact){
    printf("[%s |@-]", contact->name);
}


//Fonction relativent à la liste de contact
l_contact CreateL_contact(){
    l_contact myContactList;
    myContactList.max_level = 4;
    myContactList.head = (p_contact *) malloc(myContactList.max_level * sizeof(p_contact));
    myContactList.tail = (p_contact *) malloc(myContactList.max_level * sizeof(p_contact));
    for(int i = 0; i < myContactList.max_level; i++){
        myContactList.head[i] = NULL;
        myContactList.tail[i] = NULL;
    }
    return myContactList;
}

void Add_Head_Contact(l_contact* mylist, p_contact newcell, int level){
    // Si la liste est vide puis si la liste n'est pas  vide
    if (Is_Empty_Contact(*mylist, level)){
        mylist->head[level] = newcell;
        mylist->tail[level] = newcell;
    } else {
        newcell->next[level] = mylist->head[level];
        mylist->head[level] = newcell;
    }
}
void Add_Tail_Contact(l_contact* mylist, p_contact newcell, int level){
    // Si la liste est vide puis si la liste n'est pas vide
    if (Is_Empty_Contact(*mylist, level)){
        mylist->head[level] = newcell;
        mylist->tail[level] = newcell;
    } else {
        mylist->tail[level]->next[level] = newcell;
        mylist->tail[level] = newcell;
    }
}
void Add_contact(l_contact* mylist, p_contact newContact){
    // Calcul de niveau du contact
    newContact->level = Calcul_Contact_Level(*mylist, newContact);

    //Boucle pour chaque niveau
    for (int i = 0; i < newContact->level; i++){
        // Si on ajoute par la tête
        if (Is_Empty_Contact(*mylist, i) || strcmp(newContact->name, mylist->head[i]->name) < 0)
            Add_Head_Contact(mylist, newContact, i);


        // Si on ajoute par la queue
        else if (strcmp(newContact->name, mylist->tail[i]->name) > 0)
            Add_Tail_Contact(mylist, newContact, i);

        // Si on ajoute au millieu
        else {
            p_contact cur = mylist->head[i], prev = cur;
            while (cur != NULL){
                if (strcmp(newContact->name, prev->name) > 0 && strcmp(newContact->name, cur->name) < 0) {
                    prev->next[i] = newContact;
                    newContact->next[i] = cur;
                    break;
                }
                prev = cur;
                cur = cur->next[i];
            }
        }
    }

    //On met a jour le contact d'après
    if(newContact->next[0] != NULL) Maj_contact(mylist, newContact->next[0]);
}
void Maj_contact(l_contact* mylist, p_contact majContact){
    p_contact cur = mylist->head[0];
    while(cur->next[0] != majContact){
        cur = cur->next[0];
    }

    //On établie le futur level
    int newLevel;
    if(majContact->name[0] != cur->name[0]) newLevel = 4;      // Si on insère au niveau 3
    else if(majContact->name[0] == cur->name[0] && majContact->name[1] != cur->name[1]) newLevel = 3;      // Si on insère au niveau 2
    else if(majContact->name[0] == cur->name[0] && majContact->name[1] == cur->name[1] && majContact->name[2] != cur->name[2]) newLevel = 2;      // Si on insère au niveau 1
    else newLevel = 1;

    //Si le niveau change
    if(majContact->level != newLevel){
        //Si le nouveau niveau est supérieur
        if(newLevel > majContact->level){
            for (int i = majContact->level; i < newLevel; i++){
                // Si on ajoute par la tête
                if (Is_Empty_Contact(*mylist, i) || strcmp(majContact->name, mylist->head[i]->name) < 0)
                    Add_Head_Contact(mylist, majContact, i);

                    // Si on ajoute par la queue
                else if (strcmp(majContact->name, mylist->tail[i]->name) > 0)
                    Add_Tail_Contact(mylist, majContact, i);

                    // Si on ajoute au millieu
                else {
                    p_contact temp = mylist->head[i], prev = temp;
                    while (temp != NULL){
                        if (strcmp(majContact->name, prev->name) > 0 && strcmp(majContact->name, temp->name) < 0) {
                            prev->next[i] = majContact;
                            majContact->next[i] = temp;
                            break;
                        }
                        prev = temp;
                        temp = temp->next[i];
                    }
                }
            }
        }

        //Si le nouveau level est inférieur
        if(newLevel  < majContact->level){
            for(int i = newLevel; i < majContact->level; i++){
                p_contact temp = mylist->head[i];
                while(temp->next[i] != majContact){
                    temp = temp->next[i];
                }
                // Si on delete à la queue
                if(mylist->tail[i] == majContact){
                    temp->next[i] = NULL;
                    mylist->tail[i] = temp;
                } else {
                    temp->next[i] = majContact->next[i];
                }
            }
        }

        //On m'est a jour le contact d'après
        if(majContact->next[0] != NULL) Maj_contact(mylist, majContact->next[0]);
    }
}

int Is_Empty_Contact(l_contact mylist, int level){
    return mylist.head[level] == NULL && mylist.tail[level] == NULL;
}
int Calcul_Contact_Level(l_contact myContactList, p_contact newContact){
    // Si la liste est vide ou qu'on insère par la tête
    if(Is_Empty_Contact(myContactList, 0) || strcmp(myContactList.head[0]->name, newContact->name) > 0) return 4;
    p_contact cur = myContactList.head[0], prev = cur;

    // Si on insère par la queue
    if(strcmp(newContact->name, myContactList.tail[0]->name) > 0)
        prev = myContactList.tail[0];

    // Si on insère au millieu
    while (cur != NULL) {
        if (strcmp(newContact->name, prev->name) > 0 && strcmp(newContact->name, cur->name) < 0) break;
        prev = cur;
        cur = cur->next[0];
    }

    // On établie le futur level
    if(newContact->name[0] != prev->name[0]) return 4;      // Si on insère au niveau 3
    if(newContact->name[0] == prev->name[0] && newContact->name[1] != prev->name[1]) return 3;      // Si on insère au niveau 2
    if(newContact->name[0] == prev->name[0] && newContact->name[1] == prev->name[1] && newContact->name[2] != prev->name[2]) return 2;      // Si on insère au niveau 1
    return 1;
}
p_contact Search_Classique_Contact(l_contact myContactList, char* name){
    p_contact cur = myContactList.head[0];
    while (cur != NULL && strcmp(cur->name, name) != 0){
        cptRecherche++;
        cur = cur->next[0];
    }
    return cur;
}
p_contact Search_Contact(l_contact myContactList, char* name){
    int level = myContactList.max_level - 1;
    while(Is_Empty_Contact(myContactList, level)){
        level --;
    }

    p_contact startContact = myContactList.head[level], endContact = myContactList.tail[level];
    while(level != -1) {
        // Si start est la bonne cell
        if(!strcmp(startContact->name, name)) return startContact;
        cptRecherche ++;

        // Si end est la bonne cell
        if(!strcmp(endContact->name, name)) return endContact;
        cptRecherche ++;

        // On recherche au millieu
        // Si start est supérieur à val
        if(strcmp(startContact->name, name) > 0) startContact = myContactList.head[level - 1];

            // Si Start est inférieur à val
        else if (strcmp(endContact->name, name) < 0) endContact = myContactList.tail[level -1];

            // Si val est entre les bornes
        else {
            p_contact cur = startContact, prev = cur;
            while (strcmp(cur->name, name) < 0 || !strcmp(cur->name, name)) {
                // Si on trouve la valeur
                if (!strcmp(cur->name, name)) return cur;

                cptRecherche ++;
                prev = cur;
                cur = cur->next[level];
            }
            // On change les bornes
            startContact = prev;
            endContact = cur;
        }
        level --; // On décrémente le niveau
    }
    return NULL;
}
void Display_All_Contact(l_contact mylist){
    for(int i = 0; i < mylist.max_level; i++){
        printf("[list head_%d @-]-->", i);
        p_contact temp = mylist.head[i];
        while(temp != NULL){
            Display_contact(temp);
            printf("-->");
            temp = temp->next[i];
        }
        printf("NULL\n");
    }
}
p_contact Completion(l_contact myContactList, char* name) {
    //Si le nom correspond à quelqu'un dans la liste
    if(Search_Contact(myContactList, name) != NULL) return Search_Contact(myContactList, name);

    //Si le  nom ne correspond pas
    //On dresse une liste de nom qui commence bien
    p_contact temp = myContactList.head[0];
    while(temp != NULL){
        //Si le nom conviens
        if(strstr(temp->name, name)) {
            //On affiche
            printf("%c", temp->name[0] - 32);
            int i = 1;
            while(temp->name[i] != '_') {
                printf("%c", temp->name[i++]);
            }
            i++;
            printf(" %c", temp->name[i++] - 32);
            while(temp->name[i] != '\0'){
                printf("%c", temp->name[i++]);
            }
            printf(" | ");
        }
        temp = temp->next[0];
    }
    printf("\n");
    return NULL;
}

void Save_contact(l_contact mylist){
    char formatName[]  = "%s\n";
    FILE *stock_contact = fopen("FichierTexte/Stock_contact.txt","w");

    // Pour les contacts
    p_contact temp = mylist.head[0];
    while (temp != NULL){
        fprintf(stock_contact, formatName, temp->name);
        temp = temp->next[0];
    }

    fclose(stock_contact);
}
void Load_contact(l_contact* mylist){
    char *name = (char*) malloc(100 * sizeof(char));
    FILE *stock_contact = fopen("FichierTexte/Stock_contact.txt","r");

    if(stock_contact == NULL){
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    while(fscanf(stock_contact, "%99[^\n]\n", name) == 1){
        p_contact contact = Create_contact(name);
        Add_contact(mylist, contact);
    }

    fclose(stock_contact);
}

void Etude_Complexite_Contact(char* Name){
    l_contact MyContactList = CreateL_contact();
    Load_contact(&MyContactList);

    Display_All_Contact(MyContactList);
    printf("On recherche %s\n", Name);

    cptRecherche = 0;
    p_contact searchCalssicContact = Search_Classique_Contact(MyContactList, Name);
    printf("Pour la recherche de %s au niveau 0, on a %d comparaison\n", searchCalssicContact->name, cptRecherche);

    cptRecherche = 0;
    p_contact searchMultiContact = Search_Contact(MyContactList, Name);
    printf("Pour la recherche de %s multi-niveau, on a %d comparaison\n", searchMultiContact->name, cptRecherche);
}