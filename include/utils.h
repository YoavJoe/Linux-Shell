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

void print_directory();
void print_error_msg(char* command, char* msg);
int is_added_command(char* cmd);

#endif