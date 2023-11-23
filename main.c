#include <stdio.h>
#include <stdlib.h>

#include "module timer-20231031/timer.h"
#include "contact.h"
#include "rendez-vous.h"

int SecureAdd(int Level_S)
{
    int val = 0;
    switch (Level_S) {
        case 1 : {
            printf("1 | Mes contact.\n2 | Rechercher un contact.\n3 | Nouveau contact.\n4 | Sauvegarder et quitter.\n\n");
            printf("$ ");
            scanf("%d", &val);
            while (val < 1 || val > 4)
            {
                printf("Valeur incorrecte, veuiller saisir une autre valeur : ");
                printf("$ ");
                scanf(" %d", &val);
            }
            return val;
        }
        case 2 : {
            printf("Entrer 0 Pour revenir en arriere.\n\n");
            printf("$ ");
            scanf("%d",&val);
            while (val != 0)
            {
                printf("Valeur incorrecte, veuiller saisir une autre valeur : ");
                printf("$ ");
                scanf(" %d", &val);
            }
            return val;
        }
        case 3 : {
            printf("1 | Mes rendez-vous\n2 | Ajouter un rendez-vous\n3 | Suprimer un rendez-vous\n0 | Retour\n\n");
            printf("$ ");
            scanf("%d",&val);
            while (val < 0 || val > 3)
            {
                printf("Valeur incorrecte, veuiller saisir une autre valeur : ");
                printf("$ ");
                scanf(" %d", &val);
            }
            return val;
        }
    }
}

void main_rdv(p_contact contact){
    contact->rdv = Load_rdv(contact->name);

    while(1) {
        printf("%s :\n", contact->name); //Fonction de Tuan pour bien afficher le contact
        int val = SecureAdd(3);
        switch (val) {
            case 1: {
                //Si la liste est vide
                if(isEmptyRdv(contact->rdv))
                    printf("Vous n'avez pas de rendez vous avec ce contact.\n");

                    //Si la liste n'est pas vide
                else DisplayL_rdv(contact->rdv);

                int val1 = SecureAdd(2);
                break;
            }

            case 2 : {
                int jour, mois, annee, h, min, dh, dmin;
                do {
                    printf("Entrer la date (J/M/A) : ");
                    scanf("%d/%d/%d", &jour, &mois, &annee);
                } while(jour < 1 || jour > 31 || mois < 1 || mois > 12);

                do {
                    printf("Entrer l'heure (heure,min) : ");
                    scanf("%d,%d", &h, &min);
                } while (h < 0 || h > 23 || min < 0 || min > 59);

                do {
                    printf("Entrer la durée (heure,min) : ");
                    scanf("%d,%d", &dh, &dmin);
                } while (dh < 0 || min < 0 || min > 59);

                Add_rdv(&contact->rdv, Create_rdv(CreateDate(jour, mois, annee), CreateHour(h, min), CreateDuration(dh, dmin), CreateObject()));
                break;
            }

            case 3 : {
                int jour, mois, annee, h, min;
                do {
                    printf("Entrer la date (J/M/A) : ");
                    scanf("%d/%d/%d", &jour, &mois, &annee);
                } while(jour < 1 || jour > 31 || mois < 1 || mois > 12);

                do {
                    printf("Entrer l'heure (heure,min) : ");
                    scanf("%d,%d", &h, &min);
                } while (h < 0 || h > 23 || min < 0 || min > 59);

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

            case 0 : {
                Save_rdv(contact->rdv, contact->name);
                return;
            }
        }
    }
}

int main() {
    //On crée notre liste de contact
    l_contact MyContactList = CreateL_contact();
    Load_contact(&MyContactList);

    //Boucle infini
    while(1) {
        printf("\t\t__MON AGENDA__\n");
        int Level_S = 1;
        int val = SecureAdd(Level_S);
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

                int val1 = SecureAdd(2);
                break;
            }

            case 2: {
                //Si la liste est vide
                if(isEmptyContact(MyContactList, 0)) {
                    printf("Vous n'avez aucun contact\n");
                    int val1 = SecureAdd(2);
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
                p_contact contact = Create_contact(scanString());
                Add_contact(&MyContactList, contact);
                Save_rdv(contact->rdv, contact->name);
                break;
            }

            default: {
                Save_contact(MyContactList);
                printf("A Bientôt");
                exit(EXIT_SUCCESS);
            }
        }
    }
}