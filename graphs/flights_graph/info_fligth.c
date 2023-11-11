//
// Created by vitor on 09/11/23.
//

#include "info_fligth.h"
#include "../../memory/memory.h"

typedef struct InfoFligth{
    int number_fligh;
    double dist;
    int stop_number;
    TimeHour *duration;
}InfoFligth;

InfoFligth *sum_info_fligths(InfoFligth *self, InfoFligth *other){

    InfoFligth *sum = me_memory_alloc(NULL, sizeof(InfoFligth));
    TimeHour *sum_times = tm_sum_times(self->duration, other->duration);

    *sum = (InfoFligth){
        .duration=sum_times,
        .stop_number = self->stop_number + other->stop_number,
        .dist = self->dist + other->dist,
        .number_fligh = FAKEFLIGTH
    };
    return sum;
}
InfoFligth *diff_info_fligths(InfoFligth *self, InfoFligth *other){

    InfoFligth *diff = me_memory_alloc(NULL, sizeof(InfoFligth));
    TimeHour *diff_times = tm_diff_times(self->duration, other->duration);

    *diff = (InfoFligth){
        .duration = diff_times,
        .dist = self->dist+other->dist,
        .stop_number = self->stop_number + other->stop_number,
        .number_fligh = FAKEFLIGTH
    };
    return diff;
}

InfoFligth* create_info_fligth(int number_fligh, double dist, int stop_number, char *departure_time, char *arrival_time){

    InfoFligth *new = me_memory_alloc(NULL, sizeof(InfoFligth));
    TimeHour *departure_tm = create_time_hour_with_str(departure_time);
    TimeHour *arrival_tm = create_time_hour_with_str(arrival_time);

    *new = (InfoFligth){
        .number_fligh = number_fligh,
        .dist = dist,
        .stop_number = stop_number,
        .duration = tm_diff_times(arrival_tm, departure_tm)
    };

    return new;

}
InfoFligth *destroy_info_fligth(InfoFligth *self){
    self->duration = destroy_time_hour(self->duration);
    memset(self, 0, sizeof(InfoFligth));
    me_free(self);
    return NULL;
}

char *if_str(InfoFligth *self){
    char *duration_str = tm_str(self->duration);
    char *respost = me_formatted_str("duration: %s\nnumber fligth: %d\ndist:%f\nstop number: %d", duration_str, self->number_fligh, self->dist, self->stop_number);
    me_free(duration_str);
    return respost;
}

