//
// Created by Valentin Meltz on 03/12/2023.
//

#ifndef GESTION_AGENDA_LIB_H
#define GESTION_AGENDA_LIB_H

void clearScreen(void); // Effacer la console
void eraseBuffer(void); // Libérer le buffer

int scanMain(void); // Saisie sécurisé pour le menu
void scanBack(void); // Saisie sécurisé pour revenir en arrière
int scanRdv(void); // Saisie sécurisé pour le menu des rendez-vous

#endif //GESTION_AGENDA_LIB_H
