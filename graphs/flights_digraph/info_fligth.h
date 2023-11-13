//
// Created by vitor on 09/11/23.
//

#ifndef TRABALHO_PRATICO_GRAFOS_INFO_FLIGTH_H
#define TRABALHO_PRATICO_GRAFOS_INFO_FLIGTH_H
#include "../../time/time.h"
#define FAKEFLIGTH -1


typedef struct InfoFligth InfoFligth;

size_t if_get_tam();
InfoFligth *diff_info_fligths(InfoFligth *self, InfoFligth *other);
InfoFligth *sum_info_fligths(InfoFligth *self, InfoFligth *other);
InfoFligth *create_info_fligth_with_time_duration(int number_fligth, double dist, int stop_number, TimeHour *duration);
InfoFligth* create_info_fligth(int number_fligth, double dist, int stop_number, char *departure_time, char *arrival_time);
InfoFligth *destroy_info_fligth(InfoFligth *self);
char *if_str(InfoFligth *self);
char *tm_str(TimeHour *self);
InfoFligth * if_create_cp(InfoFligth *self);
int if_eq(InfoFligth *self, InfoFligth *other);
int if_bigger_then(InfoFligth *self, InfoFligth *other);
int if_less_then(InfoFligth *self, InfoFligth *other);
#endif //TRABALHO_PRATICO_GRAFOS_INFO_FLIGTH_H
