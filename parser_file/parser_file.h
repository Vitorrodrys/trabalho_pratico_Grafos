#ifndef CURRENT_FILE_H
#define CURRENT_FILE_H

#include <stddef.h>



typedef struct CurrentFile CurrentFile;
CurrentFile *create_parser(char *file_name);
CurrentFile *create_parser_with_txt(char *str);
char pf_get_next_char(CurrentFile *self);
char *pf_get_word_until_token(CurrentFile *self, char token);
long int pf_get_next_int(CurrentFile *self);
double pf_get_next_double(CurrentFile *self);
int pf_advance_to_word(CurrentFile *self, char *word);
void pf_return_to_file_start(CurrentFile *self);
void destroy_parser(CurrentFile *self);
int pf_is_end_file(CurrentFile *self);
#endif