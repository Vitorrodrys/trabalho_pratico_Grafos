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
#endif //TRABALHO_PRATICO_GRAFOS_TIME_H
