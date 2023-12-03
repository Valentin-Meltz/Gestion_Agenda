#include <stdio.h>
#include <stdlib.h>

#include "module timer-20231031/timer.h"
#include "lib.h"
#include "contact.h"
#include "rendez-vous.h"
#include "s_d_list.h"

void main_rdv(p_contact contact){
    contact->rdv = Load_Rdv(contact->name);

    while(1) {
        printf("%s :\n", contact->name);
        int val = scanRdv();
        switch (val) {
            case 1: {
                //Si la liste est vide
                if(Is_Empty_Rdv(contact->rdv))
                    printf("Vous n'avez pas de rendez vous avec ce contact.\n");

                    //Si la liste n'est pas vide
                else Display_L_Rdv(contact->rdv);

                scanBack();
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

                eraseBuffer();
                Add_Rdv(&contact->rdv, Create_Rdv(Create_Date(jour, mois, annee), Create_Hour(h, min), Create_Duration(dh, dmin), Create_Object()));
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

                p_rdv deleteRdv = Delete_Rdv(&contact->rdv, Create_Date(jour, mois, annee), Create_Hour(h, min));
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

            default : {
                Save_Rdv(contact->rdv, contact->name);
                Free_Rdv_List(contact->rdv);
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
        int val = scanMain();
        switch (val) {
            case 1: {
                // Affichage des contact
                printf("\t\t__Mes Contacts__\n");

                //Si la liste est vide
                if(Is_Empty_Contact(MyContactList, 0))
                    printf("Vous n'avez aucun contact.\n");

                //Si la liste n'est pas vide
                else {
                    p_contact temp = MyContactList.head[0];
                    while(temp != NULL){
                        p_contact cur = temp;
                        printf("%c :\n", temp->name[0] - 32);
                        while(cur != temp->next[3]){
                            printf("%c", cur->name[0] - 32);
                            int i = 1;
                            while(cur->name[i] != '_'){
                                printf("%c", cur->name[i++]);
                            }
                            i++;
                            printf(" %c", cur->name[i++] - 32);
                            while(cur->name[i] != '\0'){
                                printf("%c", cur->name[i++]);
                            }
                            printf("\n");
                            cur = cur->next[0];
                        }
                        printf("\n");
                        temp = temp->next[3];
                    }
                }
                scanBack();
                break;
            }

            case 2: {
                //Si la liste est vide
                if(Is_Empty_Contact(MyContactList, 0)) {
                    printf("Vous n'avez aucun contact\n");
                    scanBack();
                }

                //Si la liste n'est pas vide
                else {
                    p_contact contact = NULL;

                    //On vide le buffer
                    eraseBuffer();

                    //On fait la complétion automatique
                    do{
                        char *name = scanString();
                        contact = Completion(MyContactList, name);
                        free(name);
                    } while(contact == NULL);

                    //On lance le main pour un contact
                    main_rdv(contact);
                }

                break;
            }

            case 3: {
                //On vide le buffer
                eraseBuffer();

                //On crée un nouveau contact
                p_contact contact = Create_contact(scanString());
                Add_contact(&MyContactList, contact);
                Save_Rdv(contact->rdv, contact->name);
                break;
            }

            case 4:{
                printf("Voici comment fonctionne cette aplication : Le principe des liste à niveau.\n");
                etude_complexite_entier();
                printf("\n\n");

                //On vide le buffer
                eraseBuffer();

                Etude_Complexite_Contact(scanString());
                printf("\n\n");

                scanBack();
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