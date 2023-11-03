#ifndef GESTION_AGENDA_RENDEZ_VOUS_H
#define GESTION_AGENDA_RENDEZ_VOUS_H

//Structure de la date d'un rendez-vous
struct Date{
    int day;
    int month;
    int year;
};
typedef struct Date t_date, *p_date;

p_date CreateDate();    //Paul
void DisplayDate(p_date);   //Tuan

//Structure de l'heure et durée d'un rendez-vous
struct Hour{
    int hour;
    int minute;
};
typedef struct Hour t_hour, *p_hour, t_duration, *p_duration;

p_hour CreateHour();    //Paul
void DisplayHour(p_hour);   //Tuan
p_duration CreateDuration();    //Paul
void DisplayDuration(p_duration);   //Tuan

//Structure d'un rendez-vous
struct rendez_vous{
    p_date date;
    p_hour hour;
    p_duration duration;
    char* object;
    struct rendez_vous **next;
};
typedef struct rendez_vous t_rdv, *p_rdv;

p_rdv Create_rdv(t_date, t_hour, t_duration, char*);    //Paul
char* CreateObject();   //Paul
void Display_rdv(t_rdv);    //Tuan
void Edit_rdv(p_rdv);   //Paul

//Structure d'une liste de rendez-vous
struct list_rdv {
    t_rdv **head;
    t_rdv **tail;
};
typedef struct list_rdv l_rdv;

l_rdv CreateL_rdv();    //Paul
void DisplayL_rdv(l_rdv);   //Tuan
void Add_rdv(l_rdv*, p_rdv);    //Valentin
p_rdv Delete_rdv(l_rdv*, p_date, p_hour);   //Valentin
p_rdv Search_rdv(l_rdv, p_date, p_hour);    //Valentin
void Save_rdv();  //Pas fini (surement le txt en paramètre => chek le fonctionnement des txt en C)  //Valentin
void Load_rdv();  //Pas fini ca retournera la liste dans lequels sont stocké les rdv (surement le txt en paramètre => chek le fonctionnement des txt en C)  //Valentin

#endif //GESTION_AGENDA_RENDEZ_VOUS_H