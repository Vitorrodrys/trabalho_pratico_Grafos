//
// Created by vitor on 09/11/23.
//

#include "time.h"
#include "calendar.h"
#include "../memory/memory.h"
#include <stdio.h>
typedef struct TimeHour{
    time_t in_seconds;
    Calendar *in_data;
}TimeHour;

time_t module_seg(time_t seg){
    return ((long int )seg < 0)?seg*-1:seg;
}


TimeHour *create_time_hour_with_str(char *str){


    TimeHour *new = me_memory_alloc(NULL, sizeof(TimeHour));
    new->in_data = NULL;
    new->in_seconds = 0;
    tm_set_new_hour_with_str(new, str);
    return new;



}
TimeHour *destroy_time_hour(TimeHour *self){

    self->in_data = destroy_calendar(self->in_data);
    self->in_seconds = 0;
    me_free(self);
    return NULL;
}
TimeHour *create_time_hour_with_seconds(time_t seconds){
    TimeHour *new = me_memory_alloc(NULL, sizeof(TimeHour));

    new->in_seconds = 0;
    tm_set_new_time_hour_with_seconds(new, seconds);
    return new;

}
void add_time(TimeHour *self, time_t tm){
    self->in_seconds += tm;
    self->in_data = destroy_calendar(self->in_data);
    self->in_data = seconds_to_calend(self->in_seconds);
}
void tm_add_one_day(TimeHour *self){
    add_time(self, 86400);
}
void tm_add_one_hour(TimeHour *self){
    add_time(self, 3600);
}


void tm_set_new_hour_with_str(TimeHour *self, char *str){


    size_t tam_str = strlen(str);
    int hours;
    int min;
    char *hours_temp;
    char *mins_temp;
    int len_char_hours = (tam_str%2 == 0)?1:2;

    hours_temp = strndup(str, len_char_hours);
    mins_temp = strndup(str+len_char_hours, 2);

    hours = atoi(hours_temp);
    min = atoi(mins_temp);
    me_free_several_objects(2, &hours_temp, &mins_temp);
    hours+=((str[tam_str-1] == 'P')?12:0);
    if ( hours == 24 ){
        hours = 0;
    }
    if ( self->in_data )
        self->in_data = destroy_calendar(self->in_data);
    self->in_data = create_calendar(0,hours, min, 0);
    self->in_seconds = calend_to_seconds(self->in_data);
}
void tm_set_new_time_hour_with_seconds(TimeHour *self, time_t seconds){
    self->in_seconds = seconds;
    self->in_data = seconds_to_calend(seconds);
}
char *tm_str(TimeHour *self){
    return calend_str(self->in_data);
}
time_t tm_get_time_in_seconds(TimeHour *self){
    return self->in_seconds;
}
TimeHour *tm_sum_times(TimeHour *self, TimeHour *other){
    time_t result_in_seconds = self->in_seconds+other->in_seconds;
    return create_time_hour_with_seconds(result_in_seconds);
}

TimeHour *tm_diff_times(TimeHour *self, TimeHour *other){
    return create_time_hour_with_seconds(self->in_seconds-other->in_seconds);
}
TimeHour *tm_cp(TimeHour *self){
    return create_time_hour_with_seconds(tm_get_time_in_seconds(self));
}
int tm_eq(TimeHour *self, TimeHour *other){
    return self->in_seconds == other->in_seconds && calend_eq(self->in_data, other->in_data);
}
int tm_bigger_then(TimeHour *self, TimeHour *other){
    return self->in_seconds > other->in_seconds;
}
int tm_less_then(TimeHour *self, TimeHour *other){
    return self->in_seconds < other->in_seconds;
}