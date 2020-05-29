/*
*******************
file: myshell.h
*******************
*/
#ifndef _MYSHELL_H
#define _MYSHELL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h> /*for fork*/
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h> /*for display an error msg*/
#include "../include/LineParser.h"

#define TRUE 1
#define FALSE 0

#define PATH_MAX 100
#define BOLD_RED   "\033[1;31m"
#define BOLD_GREEN "\033[1;32m"
#define BOLD_BLUE  "\033[1;34m"
#define RESET "\033[0m"

void print_directory();
void print_error_msg(char* commend, char* msg);

/*receives a parsed line and invokes the
 command using the proper system call*/
int execute(cmdLine *pCmdLine);

int change_directory(char* path);

int is_added_commend(char* cmd);


#endif