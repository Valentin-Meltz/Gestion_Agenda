#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rendez-vous.h"

p_date CreateDate(int day, int mounth, int year){
    p_date date = (p_date) malloc(sizeof(t_date));
    date->day = day;
    date->month = mounth;
    date->year = year;
    return date;
}
void DisplayDate(p_date date){
    printf("%d/%d/%d", date->day, date->month, date->year);
}

p_hour CreateHour(int hour, int min){
    p_hour h = (p_hour) malloc(sizeof(t_hour));
    h->hour = hour;
    h->minute = min;
    return h;
}
void DisplayHour(p_hour h){
    printf("%dh%d", h->hour, h->minute);
}

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
        printf("%d min", d->minute);
}

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
    strcpy(rdv->object, object);
    rdv->next = NULL;
    return rdv;
}
void Display_rdv(p_rdv rdv){
    printf("\t");
    DisplayDate(rdv->date);
    printf(" ");
    DisplayHour(rdv->hour);
    printf("\n\t%s\n\t", rdv->object);
    DisplayDuration(rdv->duration);
}

l_rdv CreateL_rdv(){
    l_rdv mylist;
    mylist.head = NULL;
    mylist.tail = NULL;
    return mylist;
}