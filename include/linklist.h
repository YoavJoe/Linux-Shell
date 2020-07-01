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

/*This function receives command and add it to the history list
(the function use list_append function) */
void add_to_history(char* command);

/*This function receives pair of name and value and add it to environment list*/
void add_to_environment(char* name, char* value);

/*This function receives lst and data and append it to lst(history list)*/
list* list_append(list* lst, list* data);

/*This function receives location of function, 
find it(from history list) and return it*/
char* get_command(int command_location);

/*This function receives command, make list* */
list* make_new_link(char* command);

/*This function chack if the environment is empty*/
int is_environment_empty();

/*This function receives a name to delete form environment and delete it */
void delete_from_environment(char* name);

/*This function receives name to find in environment list and return it */
char* find_value(char* name);

/*This function receives pair and add to environment list*/
list* link_to_environment(char* name, char* value);

/*This function receives pair and chack if it exits in environment list*/
int is_exists(char* name, char* value);

/*This function history list*/
void print_history();

/*This function print list*/
void print_environment();

/*This function history list */
void free_history();

/*This function free the environment list */
void free_environment();

#endif