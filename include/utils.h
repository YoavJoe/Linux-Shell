/*
*******************
file: utils.h
*******************
*/
#ifndef _UTILS_H
#define _UTILS_H

#define TRUE 1
#define FALSE 0
#define CAPACITY 20 
#define MAX_COMMAND_LENGTH 128

#define PATH_MAX 100
#define BOLD_RED   "\033[1;31m"
#define BOLD_GREEN "\033[1;32m"
#define BOLD_BLUE  "\033[1;34m"
#define RESET "\033[0m"

/*This function print the currnet directory path*/
void print_directory();

/*This function receives the command and the 
error msg and print it in custom format*/
void print_error_msg(char* command, char* msg);

/*This function receives a cmd and chack if 
it's one of the added commands*/
int is_added_command(char* cmd);

/*This function receives char and chack if it's digit*/
int is_digit(char c);

/*This function receives a string and chack if it's a number*/
int is_number(char* num);

#endif