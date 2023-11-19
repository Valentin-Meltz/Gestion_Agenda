#include <stdio.h>
#include <stdlib.h>

#include "Users.h"
#include "contact.h"
#include "rendez-vous.h"

static int cptRecherche = 0;

void Main() {
    l_contact MyContactList = CreateL_contact();
    //Load_contact(&MyContactList);
    while(1) {
        printf("\t\t__MON AGENDA__\n");
        printf("\033[1m1\033[0m | Mes contact.\n\033[1m2\033[0m | Rechercher un contact.\n\033[1m3\033[0m | Nouveau contact.\n\033[1m4\033[m | Mes temps de calcul.\n\033[1m5\033[0m | Sauvegarder et quitter.\n\n");
        int val = 0;
        do {
            printf("$ ");
            scanf("%d", &val);
        } while (val < 1 || val > 5);
        switch (val) {
            case 1: {
                printf("\t\t__Mes Contacts__\n");
                //On affiche tous les contacts avec l'appels de la fonction
                DisplayAllContact(MyContactList);   //Pour l'instant
                printf("\n");
                break;
            }
            case 2: {
                p_contact contact = Search_contact(MyContactList, scanString());
                if(contact == NULL)
                    printf("Ce contact n'existe pas\n");
                else {
                    printf("%s :\n", contact->name); //Fonction de Tuan pour bien afficher le contact
                    printf("\tA | Mes rendez-vous\n\tB | Ajouter un rendez-vous\n\tC | Suprimer un rendez-vous\n\n");
                    char choix;
                    do{
                        printf("$ ");
                        scanf("%c", &choix);
                    } while ('A' != choix);
                }
                break;
            }
            case 3: {
                Add_contact(&MyContactList, Create_contact(scanString()));
                break;
            }
            case 4: {
                printf("\t\t__Mes Temps de Calculs__\n");
                printf("\033[1m1\033[0m | Mes temps avec des entiers.\n\033[1m2\033[0m | Mes temps avec mes contact.\n\n");
                int choixCalcul = 0;
                do{
                    printf("$ ");
                    scanf("%d", &choixCalcul);
                } while (choixCalcul != 1 && choixCalcul != 2);
                //On appelle la fonction d'affichage des temps de calcul
                break;
            }
            default: {
                //On sauvegarde
                exit(EXIT_SUCCESS);
            }
        }
    }
}

void Main_Contact(p_contact contact){
    printf("%s\n", contact->name); //Fonction de Tuan pour bien afficher le contact

    l_rdv mylist = contact->rdv;
    p_rdv cur = mylist.head;
    while(cur != NULL){
        DisplayDate(cur->date);
        printf(" ");
        DisplayHour(cur->hour);
        printf(" :\t");
        cur = cur->next;
    }
    printf("\n");

    cur = mylist.head;
    while(cur != NULL){
        printf("%s\t", cur->object);
        cur = cur->next;
    }
    printf("\n");

    cur = mylist.head;
    while(cur != NULL){
        DisplayDuration(cur->duration);
        printf("\t");
        cur = cur->next;
    }

}