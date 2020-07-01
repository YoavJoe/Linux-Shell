/*
*******************
file: myshell.h
*******************
*/
#ifndef _MYSHELL_H
#define _MYSHELL_H

#include "../include/LineParser.h"
#include "../include/linklist.h"
#include "../include/pipeline.h"
#include "../include/utils.h"

char* prg_name = "";

/*This function receives a parsed line and invokes the
 command using the proper system call*/
int execute(cmdLine *pCmdLine);

/*This function receives a parsed line and check if variable names appear in the 
command line with a "$" prefix, they are replaced with their associated value.*/
void check_internal_environment(cmdLine* parsedLine);

/*This function receives path and change
 the current working directory*/
int change_directory(char* path);

/*This function receives an added cmd and execute it*/
void execute_added_command(cmdLine* cmd);

/*This is the main function where the shell is running*/
int main(int argc, char** argv);

/*This function receives a pointer to cmdLine and return it's size*/
int get_size(cmdLine* cmd);

#endif