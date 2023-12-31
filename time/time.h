//
// Created by vitor on 09/11/23.
//

#ifndef TRABALHO_PRATICO_GRAFOS_TIME_H
#define TRABALHO_PRATICO_GRAFOS_TIME_H
#include <time.h>
typedef struct TimeHour TimeHour;
void tm_set_new_hour_with_str(TimeHour *self, char *str);
void tm_set_new_time_hour_with_seconds(TimeHour *self, time_t seconds);
TimeHour *create_time_hour_with_str(char *str);
TimeHour *create_time_hour_with_seconds(time_t seconds);
TimeHour *destroy_time_hour(TimeHour *self);
char *tm_get_hour_and_minute(TimeHour *self);
time_t tm_get_time_in_seconds(TimeHour *self);
TimeHour *tm_sum_times(TimeHour *self, TimeHour *other);
TimeHour *tm_diff_times(TimeHour *self, TimeHour *other);
TimeHour *tm_cp(TimeHour *self);
int tm_eq(TimeHour *self, TimeHour *other);
int tm_bigger_then(TimeHour *self, TimeHour *other);
int tm_less_then(TimeHour *self, TimeHour *other);
void tm_add_one_day(TimeHour *self);
void tm_add_one_hour(TimeHour *self);
#endif //TRABALHO_PRATICO_GRAFOS_TIME_H
