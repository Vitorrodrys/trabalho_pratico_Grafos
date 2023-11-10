//
// Created by vitor on 10/11/23.
//

#ifndef TRABALHO_PRATICO_GRAFOS_BASE_VALUE_H
#define TRABALHO_PRATICO_GRAFOS_BASE_VALUE_H
#include <stdlib.h>
typedef struct BaseValue BaseValue;
BaseValue *create_base_value(void *data, void *(*destructor)(void *), char *(*in_str)(void *), int (*eq)(void *, void *), size_t size_data);
BaseValue *destroy_base_value(BaseValue *self);
char *bv_in_str(BaseValue *self);
void *bv_get_data(BaseValue *self);
void bv_set_data(BaseValue *self, void *new_data);
int bv_equals(BaseValue *self, BaseValue *other);
size_t bv_get_tam();
#endif //TRABALHO_PRATICO_GRAFOS_BASE_VALUE_H
