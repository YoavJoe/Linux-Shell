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

/*receives a parsed line and invokes the
 command using the proper system call*/
int execute(cmdLine *pCmdLine);
void check_internal_environment(cmdLine* parsedLine);
int change_directory(char* path);
void execute_added_command(cmdLine* cmd);

/*This is the main function where the shell is running*/
int main(int argc, char** argv);

/*This function receives a pointer to cmdLine and return it's size*/
int get_size(cmdLine* cmd);

#endif