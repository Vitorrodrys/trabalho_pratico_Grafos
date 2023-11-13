//
// Created by vitor on 09/11/23.
//

#include "time.h"
#include "calendar.h"
#include "../memory/memory.h"
#include "ctype.h"
#include <stdio.h>
typedef struct TimeHour{
    time_t in_seconds;
    Calendar *in_data;
}TimeHour;


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
void tm_set_new_hour_with_str(TimeHour *self, char *str){

    char *hour = strndup(str, 2);
    char *min;
    int hour_int;
    int min_int;
    if (atoi(hour) > 12 ){
        me_free_memory((void *)&hour);
        hour = strndup(str, 1);
        min = strndup(str+1, 2);
        hour_int = atoi(hour) +  ((str[3] == 'P')?12:0);
        me_free(hour);
    }else{

        int size_char_mins = (isdigit(str[3])?2:1);
        min = strndup(str+2, size_char_mins);
        hour_int = atoi(hour) + ((str[2+size_char_mins] == 'P')?12:0);
        me_free(hour);
    }

    min_int = atoi(min);
    me_free(min);
    if ( self->in_data ){
        self->in_data = destroy_calendar(self->in_data);
    }
    self->in_data = create_calendar(0, hour_int, min_int,0);
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