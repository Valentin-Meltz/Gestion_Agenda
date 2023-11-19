#include <stdio.h>
#include <stdlib.h>

#include "Users.h"
#include "contact.h"
#include "rendez-vous.h"

void Main() {
    l_contact MyContactList = CreateL_contact();
    Load_contact(&MyContactList);
    while(1) {
        printf("\t\t__MON AGENDA__\n");
        printf("\033[1m1\033[0m | Mes contact.\n\033[1m2\033[0m | Rechercher un contact.\n\033[1m3\033[0m | Nouveau contact.\n\033[1m4\033[m | Mes temps de calcul.\n\033[1m5\033[0m | Sauvegarder et quitter.\n\n");
        int val;
        do {
            printf("$ ");
            scanf("%d", &val);
        } while (val <= 0 || val >= 6);
        switch (val) {
            case 1: {
                system("clear");
                printf("\t\t__Mes Contacts__\n");
                //On affiche tous les contacts avec l'appels de la fonction
                //Pour l'instant
                DisplayAllContact(MyContactList);
                break;
            }
            case 2: {
                //Fonction d'implémentation à partir de 3 caractère
                break;
            }
            case 3: {
                Add_contact(&MyContactList, Create_contact(scanString()));
                break;
            }
            case 4: {
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