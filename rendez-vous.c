#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rendez-vous.h"

// Fonction relativent à la date
p_date Create_Date(int day, int mounth, int year){
    p_date date = (p_date) malloc(sizeof(t_date));
    date->day = day;
    date->month = mounth;
    date->year = year;
    return date;
}
int Compare_Date(p_date date1, p_date date2){
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
void Display_Date(p_date date){
    printf("%d/%d/%d", date->day, date->month, date->year);
}

// Fonction relativent à l'heure
p_hour Create_Hour(int hour, int min){
    p_hour h = (p_hour) malloc(sizeof(t_hour));
    h->hour = hour;
    h->minute = min;
    return h;
}
int Compare_Hour(p_hour h1, p_hour h2){
    if(h1->hour == h2->hour) {
        if (h1->minute == h2->minute)
            return 2;
        return h1->minute < h2->minute;
    }
    return h1->hour < h2->hour;
}
void Display_Hour(p_hour h){
    printf("%dh%d", h->hour, h->minute);
}

// Fonction relativent à la durée
p_duration Create_Duration(int hour, int min){
    p_hour d = (p_duration ) malloc(sizeof(t_duration ));
    d->hour = hour;
    d->minute = min;
    return d;
}
void Display_Duration(p_duration d){
    if(d->hour != 0)
        printf("%dh%d", d->hour, d->minute);
    else
        printf("%dmin", d->minute);
}

// Fonction relativent au rdv
char* Create_Object(){
    char *object = (char*) malloc(100 * sizeof(char));
    printf("Quel est l'objet de ce rendez-vous ? ");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    fgets(object, 100, stdin);
    return object;
}
p_rdv Create_Rdv(p_date date, p_hour h, p_duration d, char* object){
    p_rdv rdv = (p_rdv) malloc(sizeof(t_rdv));
    rdv->date = date;
    rdv->hour = h;
    rdv->duration = d;
    rdv->object = (char*) malloc(1000 * sizeof(char));
    strcpy(rdv->object, object);
    rdv->next = NULL;
    return rdv;
}
int Compare_Rdv(p_rdv rdv1, p_rdv rdv2){
    if(Compare_Date(rdv1->date, rdv2->date) == 2)
        return Compare_Hour(rdv1->hour, rdv2->hour);
    return Compare_Date(rdv1->date, rdv2->date);
}
void Display_Rdv(p_rdv rdv){
    printf("\t");
    Display_Date(rdv->date);
    printf(" ");
    Display_Hour(rdv->hour);
    printf(" : %s\t", rdv->object);
    Display_Duration(rdv->duration);
    printf("\n");
}
void Free_Rdv(p_rdv rdv){
    free(rdv->date);
    free(rdv->hour);
    free(rdv->duration);
    free(rdv);
}

// Fonction relativent à la liste de rdv
l_rdv Create_L_rdv(){
    l_rdv mylist;
    mylist.head = NULL;
    mylist.tail = NULL;
    return mylist;
}
int Is_Empty_Rdv(l_rdv myRdvList){
    return myRdvList.head == NULL && myRdvList.tail == NULL;
}
int Is_Rdv_In_List(l_rdv myRdvlist, p_date d, p_hour h){
    if(Is_Empty_Rdv(myRdvlist)) return 0;
    if(Compare_Date(myRdvlist.head->date, d) == 2 && Compare_Hour(myRdvlist.head->hour, h) == 2) return 1;
    if(Compare_Date(myRdvlist.tail->date, d) == 2 && Compare_Hour(myRdvlist.tail->hour, h) == 2) return 1;
    p_rdv cur = myRdvlist.head;
    while (cur != myRdvlist.tail){
        if(Compare_Date(cur->date, d) == 2 && Compare_Hour(cur->hour, h) == 2) return 1;
        cur = cur->next;
    }
    return 0;
}
void Add_Head_Rdv(l_rdv* mylist, p_rdv rdv){
    if(Is_Empty_Rdv(*mylist)){
        mylist->head = rdv;
        mylist->tail = rdv;
    } else {
        rdv->next = mylist->head;
        mylist->head = rdv;
    }
}
void Add_Tail_Rdv(l_rdv* mylist, p_rdv rdv){
    if(Is_Empty_Rdv(*mylist)){
        mylist->head = rdv;
        mylist->tail = rdv;
    } else{
        mylist->tail->next = rdv;
        mylist->tail = rdv;
    }
}
void Add_Rdv(l_rdv* mylist, p_rdv rdv){
    // Si on ajoute par la tête
    if(Is_Empty_Rdv(*mylist) || Compare_Rdv(rdv, mylist->head) || Compare_Rdv(rdv, mylist->head) == 2 ){
        Add_Head_Rdv(mylist, rdv);
    }

    // Si on ajoute par la queue
    else if(Compare_Rdv(mylist->tail, rdv)){
        Add_Tail_Rdv(mylist, rdv);
    }

    // Si on ajoute au millieu
    else {
        p_rdv temp = mylist->head, prev =temp;
        while (temp != NULL){
            if (Compare_Rdv(prev, rdv) && (Compare_Rdv(rdv, temp) || Compare_Rdv(rdv, temp) == 2)){
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
p_rdv Delete_Rdv(l_rdv* mylist, p_date d, p_hour h){
    //Si il est dans la liste
    if(!Is_Rdv_In_List(*mylist, d, h)) return NULL;
    p_rdv cur = mylist->head;

    //Si il n'y as qu'un seul rendez-vous
    if(cur == mylist->tail){
        mylist->head = NULL;
        mylist->tail = NULL;
    }

    //Si il y a plusieurs rendez-vous et qu'il est a la tête
    else if(Compare_Date(cur->date, d) == 2 && Compare_Hour(cur->hour, h) == 2){
        mylist->head = cur->next;
    }

    // Si le rendez-vous est au millieu
    else{
        p_rdv prev = cur;
        while (cur != NULL){
            //Si on trouve le rendez-vous à supp
            if(Compare_Date(cur->date, d) == 2 && Compare_Hour(cur->hour, h) == 2){
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
    }
    return cur;
}
void Display_L_Rdv(l_rdv mylist){
    p_rdv cur = mylist.head;
    while(cur != NULL){
        Display_Rdv(cur);
        printf("\n");
        cur = cur->next;
    }
}
void Save_Rdv(l_rdv myRdvList, char* name){
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
l_rdv Load_Rdv(char* name){
    l_rdv myRdvList = Create_L_rdv();
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
        p_rdv rdv = Create_Rdv(Create_Date(j, m, a), Create_Hour(h, min), Create_Duration(dh, dmin), object);
        Add_Rdv(&myRdvList, rdv);
    }

    fclose(stock_rdv);
    return myRdvList;
}
void Free_Rdv_List(l_rdv myRdvlist){
    while(!Is_Empty_Rdv(myRdvlist)){
        Free_Rdv(Delete_Rdv(&myRdvlist, myRdvlist.head->date, myRdvlist.head->hour));
    }
}