#ifndef CURRENT_FILE_H
#define CURRENT_FILE_H

#include <stddef.h>



/**
 * a TAD for helping the parsing of the file
 */
typedef struct CurrentFile CurrentFile;



/**
 * create a parser from the file from the file system, the datas of the file will be mapped using mmap function for a new memory region
 * @param name_file: file that should se mapped
 * @return: a pointer for a CurrentFile, that is a TAD that supply functions for parsing of the file
 */
CurrentFile *create_parser(const char *name_file);

/**
 * create a new parser with a string received as parameter, will allocated a new string with the malloc that contain a copy of the string received
 * as parameter in heap
 * @param str: data of the parser
 * @return a pointer for a CurrentFile
 */
CurrentFile *create_parser_with_txt(char *str);


/**
 * get a next char of the buffer of the parser
 * @param self: parser that will be retired one char, the main object of the function
 * @return
 */
char pf_get_next_char(CurrentFile *self);


/**
 * get a sequence of the token of a parser, until that find a token received as parameter
 * @param self: parser
 * @param token: the token that will be the last token get in sequence token
 * @return the string of the current token until the requested token, case don't finded the token, return NULL
 */
char *pf_get_word_until_token(CurrentFile *self, char token);

/**
 * get of the next int within parser
 * @param self
 * @return the int in formatted of the char *
 */
long int pf_get_next_int(CurrentFile *self);

/**
 * get the next double within parser
 * @param self: parser
 * @return the double
 */
double pf_get_next_double(CurrentFile *self);


/**
 * advance the index that points to current char of the buffer for a new word received as parameter
 * @param self: parser
 * @param word: word that should advance within parser
 * @return true if sucess, 0 case don't
 */
int pf_advance_to_word(CurrentFile *self, char *word);

/**
 * return a index that points to current char of the buffer for the begging of the strings
 * @param self: parser
 */
void pf_return_to_file_start(CurrentFile *self);

/**
 * clear of the parser of the memory, and if this parser was created from file, will to remove the new memory region that was created
 * @param self:parser
 * @return NULL
 */
CurrentFile *destroy_parser(CurrentFile *self);


/**
 * check if is end of string of the parser
 * @param self
 * @return true if is end, false if don't
 */
int pf_is_end_file(CurrentFile *self);
#endif