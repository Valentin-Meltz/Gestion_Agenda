//
// Created by Valentin Meltz on 03/12/2023.
//

#include <stdio.h>

#include "lib.h"

void clearScreen(void) {
    printf("\033[H\033[J"); // Séquence d'échappement ANSI pour effacer l'écran
}
void eraseBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int scanMain(void) {
    printf("1 | Mes contact.\n2 | Rechercher un contact.\n3 | Nouveau contact.\n4 | Comment fonctionne l'application.\n5 | Sauvegarder et Quitter\n\n");
    printf("$ ");

    int val= 0;
    scanf(" %d", &val);
    while (val < 1 || val > 5)
    {
        printf("Valeur incorrecte, veuiller saisir une autre valeur :\n");
        printf("$ ");
        scanf(" %d", &val);
    }

    return val;
}
void scanBack(void) {
    printf("Entrer 0 Pour revenir en arriere.\n");
    printf("$ ");

    int val = 0;
    scanf(" %d",&val);
    while (val != 0)
    {
        printf("Valeur incorrecte, veuiller saisir une autre valeur :\n");
        printf("$ ");
        scanf(" %d", &val);
    }
}
int scanRdv(void) {
    printf("1 | Mes rendez-vous\n2 | Ajouter un rendez-vous\n3 | Suprimer un rendez-vous\n0 | Retour\n\n");
    printf("$ ");
    int val = 0;
    scanf(" %d",&val);
    while (val < 0 || val > 3)
    {
    printf("Valeur incorrecte, veuiller saisir une autre valeur :\n");
    printf("$ ");
    scanf(" %d", &val);
    }
    return val;
}
