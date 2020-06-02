/*
*******************
file: linklist.c
*******************
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/linklist.h"
#include "../include/utils.h"

list* head = NULL; /* listed list start */
list* last = NULL;

void add_to_history(char* command) {
    list *new_link = NULL;
    new_link = make_new_link(command);

    if (head == NULL) {
        head = list_append(head, new_link);
        last = head;
    }
    else {
        last = list_append(last, new_link);
        last = last->next;
    }
}

char* get_command(int command_location) {
    int i = 0;
    list* temp = head;

    while(i < command_location && temp != NULL) {
        temp = temp->next;
        i++;
    }

    return temp->name;
}

list* list_append(list* lst, list* data) {

    if(lst == NULL)
        return data;
    
    lst->next = data;

    return lst;

}

list* make_new_link(char* command) {
    list* new_link = (list*)malloc(sizeof(list));
    strcpy(new_link->name, command);
    new_link->next = NULL;

    return new_link;
}

void list_print() {
    list* current = head;

    while(current != NULL) {
        printf(BOLD_GREEN "%s" RESET, current->name);
        current = current->next;
    }
}

void free_list() {
    list* temp = NULL;

    while(head->next != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    free(head);
}
