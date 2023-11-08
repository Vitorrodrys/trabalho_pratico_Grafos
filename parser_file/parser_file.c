
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "../memory/memory.h"
typedef struct current_file{

    char *data;
    int current_char;
    size_t tam_file;
}current_file;

current_file *create_parser_with_txt(char *str){

    current_file *new = me_memory_alloc(NULL, sizeof(current_file));
    new->data = str;
    new->current_char = 0;
    new->tam_file = strlen(str);
    return new;

}

current_file *create_parser(char *name_file){

    current_file *new = me_memory_alloc(NULL, sizeof(current_file));

    int fd;
    struct stat file_stat;

    fd = open(name_file, O_RDONLY);
    if (fd == -1) {
        me_free_memory((void *)&new);
        return NULL;
    }

    if (fstat(fd, &file_stat) == -1) {
        me_free_memory((void *)&new);
        return NULL;
    }
    new->data = mmap(NULL, file_stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (new->data == MAP_FAILED) {
        me_free_memory((void *)&new);
        return NULL;
    }
    close(fd);
    new->tam_file= file_stat.st_size;
    new->current_char = 0;
    return new;
}

char get_next_char(current_file *self){
    if ( self->current_char == self->tam_file){
        return -1;
    }
    self->current_char++;
    return self->data[self->current_char-1];
}
char * get_word_until_token(current_file *self, char token){

    int tam= strchr(self->data+self->current_char,token) -(self->data+self->current_char );
    if(tam<=0){
        return  NULL;
    }
    char *string = strndup(self->data + self->current_char, tam);
    self->current_char += tam;
    return  string;
}
long int get_next_int(current_file *self ){
    int tmp_ind= self->current_char;
    while (isdigit(*(self->data+self->current_char))){
        self->current_char++;
    }
    char string[self->current_char-tmp_ind];
    strncpy(string, self->data+tmp_ind,(self->current_char-tmp_ind));
    string[self->current_char-tmp_ind]='\0';
   return atol(string);
}
double get_next_double(current_file *self ){
    int tmp_index= self->current_char;
    while (isdigit(*(self->data+self->current_char)) || self->data[self->current_char] =='.'){
        self->current_char++;
    }
    if (self->data[self->current_char]=='.'){
        self->current_char--;
    }
    char string[self->current_char -tmp_index];
    strncpy(string, self->data+tmp_index,(self->current_char-tmp_index));
    string[self->current_char-tmp_index]='\0';
    return atof(string);
}

int advance_to_word(current_file *self, char *word){
    char current_char = '\0';
    int index_word = 0;
    do {

        current_char = get_next_char(self);
        if(current_char == word[index_word]){
            index_word++;
        }else{
            index_word = 0;
        }

    } while (current_char != '\0' && index_word != strlen(word));
    if (index_word == strlen(word)){
        return 1;
    }else{
        return 0;
    }
}
void return_to_file_start(current_file *self){
    self->current_char = 0;
}
int is_end_file(current_file *self){
    return self->current_char == self->tam_file-1;
}

void* destroy_parser(current_file *self){
    munmap(self->data, self->tam_file);
    self->data = NULL;
}

