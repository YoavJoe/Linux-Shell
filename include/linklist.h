/*
*******************
file: linklist.h
*******************
*/
#ifndef _LINKLIST_H
#define _LINKLIST_H

#include "../include/utils.h"

typedef struct link list;

struct link {
    char name[MAX_COMMAND_LENGTH]; 
    list* next;
};

void add_to_history(char* command);
list* list_append(list* lst, list* data); /*adds the commend to history list*/
list* make_new_link(char* command);
void list_print();
void free_list(); /*free the memory of history list*/

#endif