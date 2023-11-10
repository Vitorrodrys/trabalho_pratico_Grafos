//
// Created by vitor on 09/11/23.
//

#include "time.h"
#include "../memory/memory.h"
#include "ctype.h"
#include <stdio.h>
typedef struct TimeHour{
    time_t in_seconds;
    struct tm in_data;
}TimeHour;

int _check_integrity_data(struct tm *in_data){

    return !in_data->tm_year && !in_data->tm_mon && !in_data->tm_sec;
}

TimeHour *create_time_hour_with_str(char *str){


    TimeHour *new = me_memory_alloc(NULL, sizeof(TimeHour));

    new->in_seconds = 0;
    memset(&new->in_data, 0, sizeof(struct tm));
    tm_set_new_hour_with_str(new, str);
    return new;



}
TimeHour *create_time_hour_with_seconds(time_t seconds){
    TimeHour *new = me_memory_alloc(NULL, sizeof(TimeHour));

    new->in_seconds = 0;
    memset(&new->in_data, 0, sizeof(struct tm));
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
        min_int = atoi(min);
    }else{

        int size_char_mins = (isdigit(str[3])?2:1);
        min = strndup(str+2, size_char_mins);
        hour_int = atoi(hour) + ((str[2+size_char_mins+1] == 'P')?12:0);
    }

    self->in_data.tm_hour = hour_int;
    self->in_data.tm_min = min_int;
    self->in_seconds = mktime(&self->in_data);
}
void tm_set_new_time_hour_with_seconds(TimeHour *self, time_t seconds){

    self->in_seconds = seconds;
    self->in_data = *localtime(&seconds);
    if ( !_check_integrity_data(&self->in_data) ){

        fprintf(stderr, "data was received with more fields of that hour and minute!\n");
        exit(1);
    }



}
char *tm_get_hour_and_minute(TimeHour *self){
    return me_formatted_str("%02d:%02d", self->in_data.tm_hour, self->in_data.tm_min);
}
time_t tm_get_time_in_seconds(TimeHour *self){
    return self->in_seconds;
}
TimeHour *tm_sum_times(TimeHour *self, TimeHour *other){
    time_t result_in_seconds = difftime(self->in_seconds, other->in_seconds*-1);
    return create_time_hour_with_seconds(result_in_seconds);
}

TimeHour *tm_diff_times(TimeHour *self, TimeHour *other){
    return create_time_hour_with_seconds(difftime(self->in_seconds, other->in_seconds));
}