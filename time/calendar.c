//
// Created by vitor on 11/11/23.
//

#include "calendar.h"
#include "../memory/memory.h"

typedef struct Calendar{
    int min;
    int hour;
    int day;
}Calendar;

Calendar *create_calendar(int day, int hour, int min){

    Calendar *new = me_memory_alloc(NULL, sizeof(Calendar));
    *new = (Calendar){
        .hour = hour,
        .min = min,
        .day = day
    };
    return new;
}

Calendar *seconds_to_calend(long seconds){

    int day = seconds/((long)86400);
    int hour = (seconds%86400)/3600;
    int min = (seconds%86400%3600)/60;

    return create_calendar(day, hour, min);
}

Calendar *destroy_calendar(Calendar *self){

    memset(self, 0, sizeof(Calendar));
    me_free(self);
    return NULL;
}

long calend_to_seconds(Calendar *self){
    return self->day*86400+self->hour*3600+self->min*60;
}

char *calend_str(Calendar *self){
    return me_formatted_str("day: %d,\nhour:%d,\nmin%d\n", self->day, self->hour, self->min);
}