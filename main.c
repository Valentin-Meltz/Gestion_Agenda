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
        } while (choix != 'A' && choix != 'B' && choix != 'C' && choix != 'D');

        switch (choix) {
            case 'A': {
                //Si la liste est vide
                if(isEmptyRdv(contact->rdv))
                    printf("Vous n'avez pas de rendez vous avec ce contact.\n");

                //Si la liste n'est pas vide
                else DisplayL_rdv(contact->rdv);

                int val1;
                printf("Entrer 0 pour revenir en arrière.\n");
                do {
                    printf("$ ");
                    scanf("%d", &val1);
                } while (val1 != 0);
                printf("\n\n");
                break;
            }

            case 'B': {
                int jour, mois, annee, h, min, dh, dmin;
                printf("Entrer la date (J/M/A) : ");
                scanf("%d/%d/%d", &jour, &mois, &annee);

                printf("Entrer l'heure (heure,min) : ");
                scanf("%d,%d", &h, &min);

                printf("Entrer la durée (heure,min) : ");
                scanf("%d,%d", &dh, &dmin);

                Add_rdv(&contact->rdv,Create_rdv(CreateDate(jour, mois, annee), CreateHour(h, min), CreateDuration(dh, dmin), CreateObject()));
                break;
            }

            case 'C': {
                int jour, mois, annee, h, min;
                printf("Entrer la date (J/M/A) : ");
                scanf("%d/%d/%d", &jour, &mois, &annee);

                printf("Entrer l'heure (heure,min) : ");
                scanf("%d,%d", &h, &min);

                p_rdv deleteRdv = Delete_rdv(&contact->rdv, CreateDate(jour, mois, annee), CreateHour(h, min));
                if(deleteRdv == NULL)
                    printf("Ce rendez-vous n'existe pas\n");
                else {
                    free(deleteRdv->date);
                    free(deleteRdv->hour);
                    free(deleteRdv->duration);
                    free(deleteRdv);
                }
                break;
            }

            case 'D':
                return;
        }
    }
}

int main() {
    //On crée notre liste de contact
    l_contact MyContactList = CreateL_contact();
    //Load_contact(&MyContactList);

    //Boucle infini
    while(1) {
        printf("\t\t__MON AGENDA__\n");
        printf("1 | Mes contact.\n2 | Rechercher un contact.\n3 | Nouveau contact.\n4 | Sauvegarder et quitter.\n\n");
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

                int val1;
                printf("Entrer 0 pour revenir en arrière.\n");
                do {
                    printf("$ ");
                    scanf("%d", &val1);
                } while(val1 != 0);
                printf("\n\n");
                break;
            }

            case 2: {
                //Si la liste est vide
                if(isEmptyContact(MyContactList, 0)) {
                    printf("Vous n'avez aucun contact\n");
                    int val2;
                    printf("Entrer 0 pour revenir en arrière.\n");
                    do {
                        printf("$ ");
                        scanf("%d", &val2);
                    } while (val2 != 0);
                    printf("\n\n");
                }

                //Si la liste n'est pas vide
                else {
                    p_contact contact = Search_contact(MyContactList, scanString());

                    //Si il n'existe pas
                    if (contact == NULL)
                        printf("Ce contact n'existe pas\n");

                    //Si il existe
                    else main_rdv(contact);
                }
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