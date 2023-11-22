#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rendez-vous.h"

// Fonction relativent à la date
p_date CreateDate(int day, int mounth, int year){
    p_date date = (p_date) malloc(sizeof(t_date));
    date->day = day;
    date->month = mounth;
    date->year = year;
    return date;
}
int CompareDate(p_date date1, p_date date2){
    if(date1->year == date2->year){
        if(date1->month == date2->month){
            if (date1->day == date2->day)
                return 2;
            return date1->day < date2->day;
        }
        return date1->month < date2->month;
    }
    return date1->year < date2->year;
}
void DisplayDate(p_date date){
    printf("%d/%d/%d", date->day, date->month, date->year);
}

// Fonction relativent à l'heure
p_hour CreateHour(int hour, int min){
    p_hour h = (p_hour) malloc(sizeof(t_hour));
    h->hour = hour;
    h->minute = min;
    return h;
}
int CompareHour(p_hour h1, p_hour h2){
    if(h1->hour == h2->hour) {
        if (h1->minute == h2->minute)
            return 2;
        return h1->minute < h2->minute;
    }
    return h1->hour < h2->hour;
}
void DisplayHour(p_hour h){
    printf("%dh%d", h->hour, h->minute);
}

// Fonction relativent à la durée
p_duration CreateDuration(int hour, int min){
    p_hour d = (p_duration ) malloc(sizeof(t_duration ));
    d->hour = hour;
    d->minute = min;
    return d;
}
void DisplayDuration(p_duration d){
    if(d->hour != 0)
        printf("%dh%d", d->hour, d->minute);
    else
        printf("%dmin", d->minute);
}

// Fonction relativent au rdv
char* CreateObject(){
    char *object = (char*) malloc(1000 * sizeof(char));
    do {
        printf("Quel est l'objet de ce rendez-vous ? ");
    } while (fgets(object, 1000, stdin) == NULL);
    return object;
}
p_rdv Create_rdv(p_date date, p_hour h, p_duration d, char* object){
    p_rdv rdv = (p_rdv) malloc(sizeof(t_rdv));
    rdv->date = date;
    rdv->hour = h;
    rdv->duration = d;
    rdv->object = (char*) malloc(1000 * sizeof(char));
    strcpy(rdv->object, object);
    rdv->next = NULL;
    return rdv;
}
int CompareRdv(p_rdv rdv1, p_rdv rdv2){
    if(CompareDate(rdv1->date, rdv2->date) == 2)
        return CompareHour(rdv1->hour, rdv2->hour);
    return CompareDate(rdv1->date, rdv2->date);
}
void Display_rdv(p_rdv rdv){
    printf("\t");
    DisplayDate(rdv->date);
    printf(" ");
    DisplayHour(rdv->hour);
    printf(" : %s\n\t", rdv->object);
    DisplayDuration(rdv->duration);
    printf("\n");
}

// Fonction relativent à la liste de rdv
l_rdv CreateL_rdv(){
    l_rdv mylist;
    mylist.head = NULL;
    mylist.tail = NULL;
    return mylist;
}
int isEmptyRdv(l_rdv myRdvList){
    return myRdvList.head == NULL && myRdvList.tail == NULL;
}
int isRdvInList(l_rdv myRdvlist, p_date d, p_hour h){
    if(isEmptyRdv(myRdvlist)) return 0;
    if(CompareDate(myRdvlist.head->date, d) == 2 && CompareHour(myRdvlist.head->hour, h) == 2) return 1;
    if(CompareDate(myRdvlist.tail->date, d) == 2 && CompareHour(myRdvlist.tail->hour, h) == 2) return 1;
    p_rdv cur = myRdvlist.head;
    while (cur != myRdvlist.tail){
        if(CompareDate(cur->date, d) == 2 && CompareHour(cur->hour, h) == 2) return 1;
        cur = cur->next;
    }
    return 0;
}
void Add_Head_rdv(l_rdv* mylist, p_rdv rdv){
    if(isEmptyRdv(*mylist)){
        mylist->head = rdv;
        mylist->tail = rdv;
    } else {
        rdv->next = mylist->head;
        mylist->head = rdv;
    }
}
void Add_Tail_rdv(l_rdv* mylist, p_rdv rdv){
    if(isEmptyRdv(*mylist)){
        mylist->head = rdv;
        mylist->tail = rdv;
    } else{
        mylist->tail->next = rdv;
        mylist->tail = rdv;
    }
}
void Add_rdv(l_rdv* mylist, p_rdv rdv){
    // Si on ajoute par la tête
    if(isEmptyRdv(*mylist) || CompareRdv(rdv, mylist->head) || CompareRdv(rdv, mylist->head) == 2 ){
        Add_Head_rdv(mylist, rdv);
    }

    // Si on ajoute par la queue
    else if(CompareRdv(mylist->tail, rdv)){
        Add_Tail_rdv(mylist, rdv);
    }

    // Si on ajoute au millieu
    else {
        p_rdv temp = mylist->head, prev =temp;
        while (temp != NULL){
            if (CompareRdv(prev, rdv) && (CompareRdv(rdv, temp) || CompareRdv(rdv, temp) == 2)){
                prev->next = rdv;
                rdv->next = temp;
                break;
            }
            prev = temp;
            temp = temp->next;
        }
        prev->next = rdv;
    }
}
p_rdv Delete_rdv(l_rdv* mylist, p_date d, p_hour h){
    //Si il est dans la liste
    if(!isRdvInList(*mylist, d, h)) return NULL;
    p_rdv cur = mylist->head;

    //Si il n'y as qu'un seul rendez-vous
    if(cur == mylist->tail){
        mylist->head = NULL;
        mylist->tail = NULL;
    }

    //Si il y a plusieurs rendez-vous et qu'il est a la tête
    else if(CompareDate(cur->date, d) == 2 && CompareHour(cur->hour, h) == 2){
        mylist->head = cur->next;
    }

    // Si le rendez-vous est au millieu
    else{
        p_rdv prev = cur;
        while (cur != NULL){
            //Si on trouve le rendez-vous à supp
            if(CompareDate(cur->date, d) == 2 && CompareHour(cur->hour, h) == 2){
                if(cur == mylist->tail){
                    mylist->tail = prev;
                    prev->next = NULL;
                } else
                    prev->next = cur->next;
                break;
            }
            prev = cur;
            cur = cur->next;
        }
        free(prev);
    }
    return cur;
}
void DisplayL_rdv(l_rdv mylist){
    p_rdv cur = mylist.head;
    while(cur != NULL){
        Display_rdv(cur);
        printf("\n");
        cur = cur->next;
    }
}
void Save_rdv(l_rdv myRdvList, char* name){
    char *fileName = (char*) malloc(100 * sizeof(char)); strcpy(fileName, "FichierTexte/FichierRdv/"); strcat(fileName, name); strcat(fileName, ".txt");
    char *format = "%d/%d/%d\t%d,%d\t%d,%d\t%s\n";
    FILE *stock_rdv = fopen(fileName,"w");

    if(stock_rdv == NULL){
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    p_rdv cur = myRdvList.head;
    while (cur != NULL){
        fprintf(stock_rdv, format, cur->date->day, cur->date->month, cur->date->year, cur->hour->hour, cur->hour->minute, cur->duration->hour, cur->duration->minute, cur->object);
        cur = cur->next;
    }

    fclose(stock_rdv);
}
l_rdv Load_rdv(char* name){
    l_rdv myRdvList = CreateL_rdv();
    char *fileName = (char*) malloc(100 * sizeof(char)); strcpy(fileName, "FichierTexte/FichierRdv/"); strcat(fileName, name); strcat(fileName, ".txt");
    char *format = "%d/%d/%d\t%d,%d\t%d,%d\t%s\n";

    FILE *stock_rdv = fopen(fileName,"r");

    if(stock_rdv == NULL){
        perror("Erreur lors de l'ouverture du fichier");
        return myRdvList;
    }

    int j = 0, m = 0, a = 0, h = 0, min = 0, dh = 0, dmin =0;
    char *object = (char*) malloc(1000 * sizeof(char));
    while(fscanf(stock_rdv, format, &j, &m, &a, &h, &min, &dh, &dmin, object) != EOF){
        p_rdv rdv = Create_rdv(CreateDate(j, m, a), CreateHour(h, min), CreateDuration(dh, dmin), object);
        Add_rdv(&myRdvList, rdv);
    }

    fclose(stock_rdv);
    return myRdvList;
}