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
p_date Load_date(char* date){
    char *token, **token_rdv = (char **) malloc(3 * sizeof(char *));
    token = strtok(date, "/");
    int i = 0;
    do{
        token_rdv[i++] = token;
        token = strtok(NULL, " ");
    } while(token != NULL);
    return CreateDate(atoi(token_rdv[0]), atoi(token_rdv[1]), atoi(token_rdv[2]));
}

// Fonction relativent à l'heure
p_hour CreateHour(int hour, int min){
    p_hour h = (p_hour) malloc(sizeof(t_hour));
    h->hour = hour;
    h->minute = min;
    return h;
}
int CompareHour(p_hour h1, p_hour h2){
    if(h1->hour == h2->hour)
        return h1->minute <= h2->minute;
    return h1->hour < h2->hour;
}
void DisplayHour(p_hour h){
    printf("%dh%d", h->hour, h->minute);
}
p_hour Load_hour(char* hour){
    char *token, **token_rdv = (char **) malloc(2 * sizeof(char *));
    token = strtok(hour, ",");
    int i = 0;
    do{
        token_rdv[i++] = token;
        token = strtok(NULL, " ");
    } while(token != NULL);
    return CreateHour(atoi(token_rdv[0]), atoi(token_rdv[1]));
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
p_duration Load_duration(char* d){
    char *token, **token_rdv = (char **) malloc(2 * sizeof(char *));
    token = strtok(d, ",");
    int i = 0;
    do{
        token_rdv[i++] = token;
        token = strtok(NULL, " ");
    } while(token != NULL);
    return CreateDuration(atoi(token_rdv[0]), atoi(token_rdv[1]));
}

// Fonction relativent au rdv
char* CreateObject(){
    char *object = (char*) malloc(1000 * sizeof(char));
    printf("Quel est l'objet de ce rendez-vous ? ");
    fgets(object, 1000, stdin);
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
void Delete_rdv(l_rdv* mylist, p_date date, p_hour h){
    if(date == mylist->head->date && h == mylist->head->hour){
        p_rdv rdv = mylist->head;
        mylist->head = rdv->next;
        free(rdv->date);
        free(rdv->hour);
        free(rdv->duration);
        free(rdv);
    } else{
        p_rdv temp = mylist->head, prev = temp;
        while (temp != mylist->tail && temp->date != date && temp->hour != h){
            prev = temp;
            temp = temp->next;
        }
        prev->next = temp->next;
        free(temp->date);
        free(temp->hour);
        free(temp->duration);
        free(temp);
    }
}   //
void DisplayL_rdv(l_rdv mylist){
    p_rdv cur = mylist.head;
    while(cur != NULL){
        Display_rdv(cur);
        printf("\n");
        cur = cur->next;
    }
}
p_rdv Search_rdv(l_rdv mylist, p_date date, p_hour h){
    if(mylist.head->date == date && mylist.head->hour == h) return mylist.head;
    if(mylist.tail->date == date && mylist.tail->hour == h) return mylist.tail;
    p_rdv temp = mylist.head;
    while (temp != NULL){
        if(temp->date == date && temp->hour == h) return temp;
        temp = temp->next;
    }
    return NULL;
}   //
p_rdv Load_rdv(char* rdv){
    char *token, **token_rdv = (char **) malloc(4 * sizeof(char *));
    token = strtok(rdv, " ");
    int i = 0;
    do{
        token_rdv[i++] = token;
        token = strtok(NULL, " ");
    } while(token != NULL);
    p_date date = Load_date(token_rdv[0]);
    p_hour h = Load_hour(token_rdv[1]);
    p_duration d = Load_duration(token_rdv[2]);
    return Create_rdv(date, h, d, token_rdv[3]);
}   //