//
// Created by vitor on 21/11/23.
//

#ifndef TRABALHO_PRATICO_GRAFOS_STRING_H
#define TRABALHO_PRATICO_GRAFOS_STRING_H

#include <string.h>

/**
 * concat two strings, generating other string, the memory of the new string is obtained with malloc
 * @param str: first string of the concatening
 * @param other: second string of the cocatening
 * @return: a new string that is the junction of the two strings
 * */
char *str_concat(char *str, char *other);

/**
 * create a string formatted in memory, similar to printf, but don't will stored the string in the stdout, will store in a string dynamically allocated by malloc
 * @param control_str: the control str that should be passed, similar to "%s %d %f"
 * @param ... variable args that will be inserted in the strings
 * @return the string formatted
 */
char *str_formatted(char *control_str, ...);

/**
 * concat multiplies string received with variable args, use the str_concat to concat in pairs of two in two
 * @param quantitys: quantity of the strings that will be received as variable args
 * @param ... variabel number of the strings, that will be used in concatening
 * @return the product of the all strings
 */
char *str_concat_multiplies(int quantitys, ...);

/**
 * convert a int in str
 * @param number: number that will be converted
 * @return a string that contain of the number
 */
char* convert_int_to_str(int number);

/**
 * will repeat a string n times, being N received as parameter in times
 * @param string: the string that should be repeat
 * @param times: how many times should repeat
 * @return: a new string allocated dinamically, that contains the parameter string repeated N times
 */
char *str_multiply_str(char *string, int times);

/**
 *
 * destroy a str, this functions only is used in create_base_value, because the base_value needs of the a destructor function by can clear
 * the memory region of the generic data that it received
 * @param str: the string that will be destroyed, in all parts of the code, this parameters is received by a function pointer,
 * because of the this function is stored in a function pointer of a base_value, and when it was destroyed, then the destructor of the base_Value will call
 * the function pointer stored within it, that will be this function
 * @return NULL
 */
void *destroy_str(char *str);


/**
 * this functions only is needs for create_base_value, because by default a base_value needs of the function of transforming of the generic
 * data in str, then is needed pass it for create_base_value
 * @param str
 * @return
 */
char* str_str(char *str);

#endif //TRABALHO_PRATICO_GRAFOS_STRING_H
