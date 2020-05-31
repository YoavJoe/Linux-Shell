/*
*******************
file: linklist.c
*******************
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/linklist.h"

list* head = NULL; /* listed list start */
list* last = NULL;

list* list_append(list* lst, list* data) {

    if(lst == NULL)
        return data;
    
    lst->next = data;

    return data;

}

list* make_new_link(char* name) {
    list* new_link = (list*)malloc(sizeof(list));
    new_link->name = name;
    new_link->next = NULL;

    return new_link;

}

void list_print(list* lst) {
    list* current = lst;

    while(current != NULL) {
        printf(BOLD_GREEN "%s" RESET, current->name);
        current = current->next;
    }
}

void free_list(list* lst) {
    list* temp = NULL;

    while(lst->next != NULL) {
        temp = lst;
        lst = head->next;
        free(temp);
    }
    free(lst);
}
