/*
*******************
file: linklist.h
*******************
*/
#ifndef _LINKLIST_H
#define _LINKLIST_H

#define BOLD_GREEN "\033[1;32m"
#define RESET "\033[0m"

typedef struct link list;

struct link {
    char* name; 
    list* next;
};

list* list_append(list* lst, list* data); /*adds the commend to history list*/
list* make_new_link(char* name);
void list_print(list* lst);
void free_list(list* lst); /*free the memory of history list*/

#endif