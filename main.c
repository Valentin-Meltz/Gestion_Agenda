#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>

#include "module timer-20231031/timer.h"
#include "s_d_list.h"
#include "contact.h"
#include "rendez-vous.h"
#include "Users.h"

void main_rdv(p_contact contact){
    while(1) {
        printf("%s :\n", contact->name); //Fonction de Tuan pour bien afficher le contact
        printf("A | Mes rendez-vous\nB | Ajouter un rendez-vous\nC | Suprimer un rendez-vous\nD | Retour\n\n");
        char choix;
        do {
            printf("$ ");
            scanf("%c", &choix);
        } while (choix != 'A' && choix != 'B' && choix != 'C');

        switch (choix) {
            //On affiche les rendez-vous
            case 'A': {
                DisplayL_rdv(contact->rdv);
                break;
            }

                //On ajoute un contact
            case 'B': {
                int jour, mois, annee, h, min, dh, dmin;
                printf("Entrer la date (J/M/A) : ");
                scanf("%d/%d/%d", &jour, &mois, &annee);

                printf("Entrer l'heure (heure,min) : ");
                scanf("%d,%d", &h, &min);

                printf("Entrer la durée (heure,min) : ");
                scanf("%d,%d", &dh, &dmin);

                Add_rdv(&contact->rdv,
                        Create_rdv(CreateDate(jour, mois, annee), CreateHour(h, min), CreateDuration(dh, dmin),
                                   CreateObject()));
                break;
            }

            case 'C': {
                int jour, mois, annee, h, min;
                printf("Entrer la date (J/M/A) : ");
                scanf("%d/%d/%d", &jour, &mois, &annee);

                printf("Entrer l'heure (heure,min) : ");
                scanf("%d,%d", &h, &min);

                Delete_rdv(&contact->rdv, CreateDate(jour, mois, annee), CreateHour(h, min));
                break;
            }

            case 'D':
                break;
        }
        return;
    }
}

int main() {
    //On crée notre liste de contact
    l_contact MyContactList = CreateL_contact();
    //Load_contact(&MyContactList);

    //Boucle infini
    while(1) {
        //Menu principal
        printf("\t\t__MON AGENDA__\n");
        printf("\033[1m1\033[0m | Mes contact.\n\033[1m2\033[0m | Rechercher un contact.\n\033[1m3\033[0m | Nouveau contact.\n\033[1m4\033[m | Sauvegarder et quitter.\n\n");
        int val = 0;
        do {
            printf("$ ");
            scanf("%d", &val);
        } while (val < 1 || val > 4);

        switch (val) {
            case 1: {
                // Affichage des contact
                printf("\t\t__Mes Contacts__\n");

                //Si la liste est vide
                if(isEmptyContact(MyContactList, 0))
                    printf("Vous n'avez aucun contact.\n");

                //Si la liste n'est pas vide
                else
                    DisplayAllContact(MyContactList);

                int val2;
                printf("Entrer 0 pour revenir en arrière.\n");
                do {
                    printf("$ ");
                    scanf("%d", &val2);
                } while(val2 != 0);
                printf("\n\n");
                break;
            }

            case 2: {
                //On recherche un contact
                p_contact contact = Search_contact(MyContactList, scanString());

                //Si il n'existe pas //Marche pas encore
                if(contact == NULL)
                    printf("Ce contact n'existe pas\n");

                //Si il existe
                else main_rdv(contact);
                break;
            }

            case 3: {
                Add_contact(&MyContactList, Create_contact(scanString()));
                break;
            }

            default: {
                //On sauvegarde
                exit(EXIT_SUCCESS);
            }
        }
    }
    return 0;
}