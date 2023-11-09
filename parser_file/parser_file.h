#ifndef CURRENT_FILE_H
#define CURRENT_FILE_H

#include <stddef.h>



typedef struct current_file current_file;
current_file *create_parser(char *file_name);
current_file *create_parser_with_txt(char *str);
char pf_get_next_char(current_file *self);
char *pf_get_word_until_token(current_file *self, char token);
long int pf_get_next_int(current_file *self);
double pf_get_next_double(current_file *self);
int pf_advance_to_word(current_file *self, char *word);
void pf_return_to_file_start(current_file *self);
void destroy_parser(current_file *self);
int pf_is_end_file(current_file *self);
#endif