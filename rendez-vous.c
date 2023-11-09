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
int CompareDate(p_date date1, p_date date2){
    if(date1->year == date2->year){
        if(date1->month == date2->month) {
            if (date1->day == date2->day)
                return 2;
            return date1->day < date2->year;
        }
        return date1->month < date2->month;
    }
    return date1->year < date2->year;
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
int CompareHour(p_hour h1, p_hour h2){
    if(h1->hour == h2->hour)
        return h1->minute <= h2->minute;
    return h1->hour < h2->hour;
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
    printf("\n\t%s\n\t", rdv->object);
    DisplayDuration(rdv->duration);
}

l_rdv CreateL_rdv(){
    l_rdv mylist;
    mylist.head = NULL;
    mylist.tail = NULL;
    return mylist;
}
void DisplayL_rdv(l_rdv mylist){
    p_rdv cur = mylist.head;
    while(cur != NULL){
        Display_rdv(cur);
        printf("\n");
        cur = cur->next;
    }
}
void Add_Head_list(l_rdv* mylist, p_rdv rdv){
    if(mylist->head == NULL && mylist->tail == NULL){
        mylist->head = rdv;
        mylist->tail = rdv;
        return;
    }
    rdv->next = mylist->head;
    mylist->head = rdv;
}
void Add_Tail_List(l_rdv* mylist, p_rdv rdv){
    if(mylist->head == NULL && mylist->tail == NULL){
        mylist->head = rdv;
        mylist->tail = rdv;
        return;
    }
    mylist->tail->next = rdv;
    mylist->tail = rdv;
}
void Add_rdv(l_rdv* mylist, p_rdv rdv){
    if(CompareRdv(rdv, mylist->head) || CompareRdv(rdv, mylist->head) == 2 || mylist->head == NULL && mylist->tail == NULL){
        Add_Head_contact(mylist, rdv);
    } else if(CompareRdv(mylist->tail, rdv)){
        Add_Tail_contact(mylist, rdv);
    } else {
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
}