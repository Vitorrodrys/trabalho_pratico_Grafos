//
// Created by vitor on 11/11/23.
//

#ifndef TRABALHO_PRATICO_GRAFOS_CALENDAR_H
#define TRABALHO_PRATICO_GRAFOS_CALENDAR_H


typedef struct Calendar Calendar;

Calendar *create_calendar(int day, int hour, int min, int seg);
Calendar *seconds_to_calend(long seconds);
Calendar *destroy_calendar(Calendar *self);
long calend_to_seconds(Calendar *self);
char *calend_str(Calendar *self);
Calendar * calend_cp(Calendar *self);
int calend_eq(Calendar *self, Calendar *other);
#endif //TRABALHO_PRATICO_GRAFOS_CALENDAR_H
