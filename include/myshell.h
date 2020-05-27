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
#include <unistd.h>
#include "../include/LineParser.h"

#define TRUE 1
#define FALSE 0

/*receives a parsed line and invokes the
 command using the proper system call*/
int execute(cmdLine *pCmdLine);


#endif