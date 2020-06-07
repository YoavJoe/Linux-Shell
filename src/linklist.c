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

list* environment = NULL;

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

void add_to_environment(char* name, char* value) {
    list* to_add = NULL;

    if(is_exists(name, value))
        return;

    to_add = link_to_environment(name, value);
    if(environment == NULL)
        environment = to_add;
    else {
        to_add->next = environment;
        environment = to_add;
    }
}

int is_exists(char* name, char* value) {
    list* current = environment;

    while(current != NULL) {
        if(strcmp(name, current->name) == 0) {
            current->value = (char*)realloc(current->value, strlen(value) + 1);
            strcpy(current->value, value);
            return TRUE;
        }
        current = current->next;
    }

   return FALSE;   
}

char* find_value(char* name) {
    list* curr = environment;
    
    while(!is_environment_empty() && strcmp(curr->name, name) != 0)
        curr = curr->next;
    if(curr == NULL)
        return NULL;
    return curr->value;
}

void delete_from_environment(char* name) {
    list* temp = environment, *prev = NULL;

    /*if head itslef holds the key to delete*/
    if(temp != NULL && strncmp(temp->name, name, 1) == 0) {
        environment = temp->next; /*change head*/
        /*free old head*/
        free(temp->name);
        free(temp->value);
        free(temp);
        return;
    }

    while(temp != NULL && strncmp(temp->name, name, 1) != 0) {
        prev = temp;
        temp = temp->next;
    }
    if(temp == NULL) return;

    prev->next = temp->next; /*unlink the node linked list*/

    free(temp->name);
    free(temp->value);
    free(temp);
}

list* link_to_environment(char* name, char* value) {
    list* new = (list*)malloc(sizeof(list));
    new->name = (char*)malloc(strlen(name) + 1);
    new->value = (char*)malloc(strlen(value) + 1);
    strcpy(new->name, name);
    strcpy(new->value, value);
    new->next = NULL;
    return new;
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

int is_environment_empty() {
    if(environment == NULL)
        return TRUE;
    return FALSE;
}

list* list_append(list* lst, list* data) {
    if(lst == NULL)
        return data;
    lst->next = data;
    return lst;
}

list* make_new_link(char* command) {
    list* new_link = (list*)malloc(sizeof(list));
    new_link->name =  malloc(strlen(command)+ 1);
    strcpy(new_link->name, command);
    new_link->next = NULL;

    return new_link;
}

void print_history() {
    list* current = head;

    while(current != NULL) {
        printf(BOLD_GREEN "%s" RESET, current->name);
        current = current->next;
    }
}

void print_environment() {
    list* current = environment;

    while(current != NULL) {
        printf(BOLD_GREEN "name: %s " RESET, current->name);
        printf(BOLD_GREEN "value: %s" RESET, current->value);
        printf("\n");
        current = current->next;
    }
}

void free_history() {
    list* temp = NULL;

    while(head != NULL) {
        temp = head;
        head = head->next;
        free(temp->name);
        free(temp);
    }
}

void free_environment() {
    list* temp = NULL;

    while(environment != NULL) {
        temp = environment;
        environment = environment->next;
        free(temp->name);
        free(temp->value);
        free(temp);
    }
}