#ifndef GESTION_AGENDA_RENDEZ_VOUS_H
#define GESTION_AGENDA_RENDEZ_VOUS_H

//Structure de la date d'un rendez-vous
struct Date{
    int day;
    int month;
    int year;
};
typedef struct Date t_date, *p_date;

p_date CreateDate(int, int, int);
int CompareDate(p_date, p_date);
void DisplayDate(p_date);


//Structure de l'heure et durée d'un rendez-vous
struct Hour{
    int hour;
    int minute;
};
typedef struct Hour t_hour, *p_hour, t_duration, *p_duration;

p_hour CreateHour(int, int);
int CompareHour(p_hour , p_hour);
void DisplayHour(p_hour);

p_duration CreateDuration(int, int);
void DisplayDuration(p_duration);

//Structure d'un rendez-vous
struct rendez_vous{
    p_date date;
    p_hour hour;
    p_duration duration;
    char* object;
    struct rendez_vous *next;
};
typedef struct rendez_vous t_rdv, *p_rdv;

p_rdv Create_rdv(p_date, p_hour, p_duration, char*);
char* CreateObject();
int CompareRdv(p_rdv, p_rdv);
void Display_rdv(p_rdv);

//Structure d'une liste de rendez-vous
struct list_rdv {
    t_rdv *head;
    t_rdv *tail;
};
typedef struct list_rdv l_rdv;

l_rdv CreateL_rdv();
int isEmptyRdv(l_rdv);
int isRdvInList(l_rdv, p_date, p_hour);
void Add_Head_rdv(l_rdv*, p_rdv);
void Add_Tail_rdv(l_rdv*, p_rdv);
void Add_rdv(l_rdv*, p_rdv);
p_rdv Delete_rdv(l_rdv*, p_date, p_hour);
void DisplayL_rdv(l_rdv);
void Save_rdv(l_rdv, char*);
l_rdv Load_rdv(char*);

#endif //GESTION_AGENDA_RENDEZ_VOUS_H