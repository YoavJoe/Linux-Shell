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
    char* name;
    char* value;
    list* next;
};

void add_to_history(char* command);
void add_to_environment(char* name, char* value);
list* list_append(list* lst, list* data); /*adds the commend to history list*/
char* get_command(int command_location); /*get the command from history list*/
list* make_new_link(char* command);
int is_environment_empty();
void delete_from_environment(char* name);
char* find_value(char* name);
list* link_to_environment(char* name, char* value);
int is_exists(char* name, char* value);
void print_history();
void print_environment();
void free_history(); /*free the memory of history list*/
void free_environment();

#endif