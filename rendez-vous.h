#ifndef GESTION_AGENDA_RENDEZ_VOUS_H
#define GESTION_AGENDA_RENDEZ_VOUS_H

//Structure de la date d'un rendez-vous
struct Date{
    int day;
    int month;
    int year;
};
typedef struct Date t_date, *p_date;

p_date Create_Date(int, int , int);
int Compare_Date(p_date, p_date);
void Display_Date(p_date);


//Structure de l'heure et durée d'un rendez-vous
struct Hour{
    int hour;
    int minute;
};
typedef struct Hour t_hour, *p_hour, t_duration, *p_duration;

p_hour Create_Hour(int, int);
int Compare_Hour(p_hour , p_hour);
void Display_Hour(p_hour);

p_duration Create_Duration(int, int);
void Display_Duration(p_duration);

//Structure d'un rendez-vous
struct rendez_vous{
    p_date date;
    p_hour hour;
    p_duration duration;
    char* object;
    struct rendez_vous *next;
};
typedef struct rendez_vous t_rdv, *p_rdv;

p_rdv Create_Rdv(p_date, p_hour, p_duration, char*);
char* Create_Object(void);
int Compare_Rdv(p_rdv, p_rdv);
void Display_Rdv(p_rdv);
void Free_Rdv(p_rdv);

//Structure d'une liste de rendez-vous
struct list_rdv {
    t_rdv *head;
    t_rdv *tail;
};
typedef struct list_rdv l_rdv;

l_rdv Create_L_rdv(void);
int Is_Empty_Rdv(l_rdv);
int Is_Rdv_In_List(l_rdv, p_date, p_hour);
void Add_Head_Rdv(l_rdv*, p_rdv);
void Add_Tail_Rdv(l_rdv*, p_rdv);
void Add_Rdv(l_rdv*, p_rdv);
p_rdv Delete_Rdv(l_rdv*, p_date, p_hour);
void Display_L_Rdv(l_rdv);
void Save_Rdv(l_rdv, char*);
l_rdv Load_Rdv(char*);
void Free_Rdv_List(l_rdv);

#endif //GESTION_AGENDA_RENDEZ_VOUS_H