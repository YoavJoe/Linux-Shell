/*
*******************
file: pipeline.h
*******************
*/
#ifndef _PIPELINE_H
#define _PIPELINE_H

#define STDIN 0
#define STDOUT 1

/*This function receives the number of required pipes
and returns an array of pipes*/
int **create_pipes(int n);

/*This function receives an array of pipes and an integer
indicating the size of the array. The function releases all
memory dedicated to the pipes*/
void release_pipes(int **pipes, int n);

/*This function receives an array of pipes and a pointer
to a cmdLine structure. It returns the pipe which feeds
the process associated with the command. That is, 
the pipe that appears to the left of the process name in the command line.*/
int *left_pipe(int **pipes, cmdLine* pCmdLine);

/*This function receives an array of pipes and a pointer
to a cmdLine structure. It returns the pipe which feeds
the process associated with the command. That is, 
the pipe that appears to the right of the process name in the command line.*/
int *right_pipe(int **pipes, cmdLine *pCmdLine);

#endif