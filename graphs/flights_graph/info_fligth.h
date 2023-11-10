//
// Created by vitor on 09/11/23.
//

#ifndef TRABALHO_PRATICO_GRAFOS_INFO_FLIGTH_H
#define TRABALHO_PRATICO_GRAFOS_INFO_FLIGTH_H
#include "../../time/time.h"
typedef struct InfoFligth{

    TimeHour *flight_departure;
    TimeHour *flight_arrival;
    int number_fligh;
    int stops_number;

}InfoFligth;

#endif //TRABALHO_PRATICO_GRAFOS_INFO_FLIGTH_H
