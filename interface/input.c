//
// Created by vitor on 21/11/23.
//

#include "input.h"
#include "stdio.h"
#include "../memory/memory.h"
#include "../parser_file/parser_file.h"


char *get_text(char stop_in){

    char *text = me_memory_alloc(NULL, sizeof(char)*2);
    int size = 2;
    do {
        text[size-2] = fgetc(stdin);
        if ( text[size-2] != stop_in ){
            size++;
            text = me_memory_alloc(text, sizeof(char )*size);
        }

    } while (text[size-2] != stop_in);
    text[size-2] = '\0';
    return text;

}
void get_number(char *formatted, void *ptr){

    int is_correct = 0;
    do {
        is_correct = 0;
        scanf(formatted, ptr);

        while (fgetc(stdin) != '\n')
            is_correct++;
        if (is_correct){
            printf("please, type only numbers!\n");
        }
    } while (is_correct);
}