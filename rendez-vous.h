#ifndef GESTION_AGENDA_RENDEZ_VOUS_H
#define GESTION_AGENDA_RENDEZ_VOUS_H

struct Date{
    int day;
    int month;
    int year;
};
typedef struct Date t_date, *p_date;

struct Hour{
    int hour;
    int minute;
};
typedef struct Hour t_hour, *p_hour, t_duration, *p_duration;

struct rendez_vous{
    p_date date;
    p_hour hour;
    p_duration duration;
    char* object;
};
typedef struct rendez_vous t_rdv, *p_rdv;

#endif //GESTION_AGENDA_RENDEZ_VOUS_H
