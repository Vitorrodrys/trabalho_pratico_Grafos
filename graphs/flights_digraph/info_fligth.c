//
// Created by vitor on 09/11/23.
//

#include "info_fligth.h"
#include "../../memory/memory.h"
#include <stdarg.h>
#include "../../string/string.h"
typedef struct InfoFligth{
    LinkedList *number_fligths;
    //list of flight numbers that this InfoFlight is referenced, in matrix of flights,
    //this list any have one element, because each edge representing one InfoFlight, but in dijkstra, when two
    //edge are added, the new InfoFlight generated have a concatenation of the list of flights of the first InfoFlight and second InfoFlight
    double dist;
    int stop_number;
    TimeHour *duration;

}InfoFligth;

LinkedList *_create_list_fligths(int quantity_fligths, ...){

    va_list number_fligths;
    va_start(number_fligths, quantity_fligths);

    LinkedList *list = create_linked_list();
    int current_fligth;
    for (int i = 0; i < quantity_fligths; ++i) {
        current_fligth = va_arg(number_fligths, int);
        lkl_append(
                list,
                create_base_value(
                        create_int(current_fligth),
                        (void *)destroy_int,
                        (void *) me_int_to_str,
                        (void *)me_eq_int,
                        sizeof(int)
                        )
                );
    }
    va_end(number_fligths);
    return list;

}
LinkedList *_create_fligth_list_from_fligth_list(LinkedList *from_fligth_list){

    LinkedList *new = create_linked_list();
    int *current_value;
    for (int i = 0; i < lkl_get_tam(from_fligth_list); ++i) {

        current_value = lkl_get_data(from_fligth_list, i);
        lkl_append(
                new,
                create_base_value(
                        create_int(*current_value),
                        (void *)destroy_int,
                        (void *) me_int_to_str,
                        (void *)me_eq_int,
                        sizeof(int)
                        )
                );
    }
    return new;
}

size_t if_get_tam(){
    return sizeof(InfoFligth);
}

InfoFligth *sum_info_fligths(InfoFligth *self, InfoFligth *other){

    InfoFligth *sum = me_memory_alloc(NULL, sizeof(InfoFligth));
    TimeHour *sum_times = tm_sum_times(self->duration, other->duration);

    *sum = (InfoFligth){
        .duration=sum_times,
        .stop_number = self->stop_number + other->stop_number,
        .dist = self->dist + other->dist,
        .number_fligths = lkl_concat_lists(self->number_fligths, other->number_fligths)
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
        .number_fligths = FAKEFLIGTH
    };
    return diff;
}

InfoFligth* create_info_fligth(int number_fligth, double dist, int stop_number, char *departure_time, char *arrival_time){

    InfoFligth *new = me_memory_alloc(NULL, sizeof(InfoFligth));
    TimeHour *departure_tm = create_time_hour_with_str(departure_time);
    TimeHour *arrival_tm = create_time_hour_with_str(arrival_time);

    if (tm_less_then(arrival_tm, departure_tm) ){
        tm_add_one_day(arrival_tm);
    }

    *new = (InfoFligth){
        .number_fligths = _create_list_fligths(1, number_fligth),
        .dist = dist,
        .stop_number = stop_number,
        .duration = tm_diff_times(arrival_tm, departure_tm)
    };

    return new;
}
InfoFligth *create_info_fligth_with_time_duration(LinkedList *list_fligths, double dist, int stop_number, TimeHour *duration){

    InfoFligth *new = me_memory_alloc(NULL, sizeof(InfoFligth));
    *new = (InfoFligth){
        .duration = duration,
        .dist = dist,
        .stop_number = stop_number,
        .number_fligths = list_fligths
    };
    return new;
}
InfoFligth *destroy_info_fligth(InfoFligth *self){
    self->duration = destroy_time_hour(self->duration);
    self->number_fligths = destroy_lkl(self->number_fligths);
    memset(self, 0, sizeof(InfoFligth));
    me_free(self);
    return NULL;
}

char *if_str(InfoFligth *self){
    char *duration_str = tm_str(self->duration);
    char *list_fligths_in_str = lkl_str(self->number_fligths);
    char *respost = str_formatted("duration: %s | number flights: %s | dist:%.2f | stop number: %d ", duration_str, list_fligths_in_str, self->dist, self->stop_number);
    me_free(duration_str);
    me_free(list_fligths_in_str);
    return respost;
}
InfoFligth* if_create_cp(InfoFligth *self){
    InfoFligth *cp = me_memory_alloc(NULL, sizeof(InfoFligth));

    *cp = (InfoFligth){
        .number_fligths = _create_fligth_list_from_fligth_list(self->number_fligths),
        .duration = tm_cp(self->duration),
        .stop_number = self->stop_number,
        .dist = self->dist
        };
    return cp;
}
int if_eq(InfoFligth *self, InfoFligth *other){
    return
    self->stop_number == other->stop_number && self->dist == other->dist &&
    lkl_eq(self->number_fligths, other->number_fligths) && tm_eq(self->duration, other->duration);
}

int if_bigger_then_in_duration(InfoFligth *self, InfoFligth *other){
    return
    tm_bigger_then(self->duration, other->duration);
}

int if_bigger_then_in_dist(InfoFligth *self, InfoFligth *other){
    return self->dist > other->dist;
}
int if_less_then_in_duration(InfoFligth *self, InfoFligth *other){
    return tm_less_then(self->duration, other->duration);
}
int if_less_then_in_dist(InfoFligth *self, InfoFligth*other){
    return self->dist < other->dist;
}
InfoFligth *if_sum_fligths(InfoFligth *self, InfoFligth *other){
    LinkedList *self_cp = _create_fligth_list_from_fligth_list(self->number_fligths);
    LinkedList *other_cp = _create_fligth_list_from_fligth_list(other->number_fligths);
    InfoFligth *sum = me_memory_alloc(NULL, sizeof(InfoFligth));
    *sum = (InfoFligth){
        .number_fligths = lkl_concat_lists(self_cp, other_cp),
        .dist = self->dist + other->dist,
        .stop_number = self->stop_number + other->stop_number,
        .duration = tm_sum_times(self->duration, other->duration)
    };
    return sum;
}

LinkedList *ifa_get_number_fligths(InfoFligth *self){
    return _create_fligth_list_from_fligth_list(self->number_fligths);
}