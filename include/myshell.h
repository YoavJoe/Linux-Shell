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
#include "../include/LineParser.h"
#include "../include/linklist.h"
#include "../include/utils.h"

char* prg_name = "";

/*receives a parsed line and invokes the
 command using the proper system call*/
int execute(cmdLine *pCmdLine);
int change_directory(char* path);
int main(int argc, char** argv);

#endif