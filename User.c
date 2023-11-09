#include "User.h"
#include <stdio.h>

int Menu()
{
    int v;
    for(int i = 0;i<75;i++)
    {
        printf("%c",'-');
    }
    printf("\n|| 1. Rechercher un contact                                              ||\n|| 2. Afficher les rendez-vous d\'un contact                              ||\n|| 3. Creer un contact                                                   ||\n|| 4. Creer un rendez-vous pour un contact                               ||\n|| 5. Supprimer un rendez-vous                                           ||\n|| 6. Sauvegarder le fichier de tous les rendez-vous                     ||\n|| 7. Charger un fichier de rendez-vous                                  ||\n|| 8. Fournir les temps de calcul pour une insertion de nouveau contact  || \n");
    for(int i = 0;i<75;i++)
    {
        printf("%c",'-');
    }
    printf("\nVeuiller choisir un action a realiser : ");
    scanf("%d",&v);
    switch (v) {
        case 1:{
            Main_A(?);
            break;
        }
        case 2:{
            Main_B(?);
            break;
        }
        case 3:{
            Main_C(?);
            break;
        }
        case 4:{
            Main_D(?);
            break;
        }
        case 5:{
            Main_E(?);
            break;
        }
        case 6:{
            Main_F(?);
            break;
        }
        case 7:{
            Main_G(?);
            break;
        }
        case 8:{
            Main_H(?);
            break;
        }
        default:{

        }
    }
    return v;
}