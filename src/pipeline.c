/*
*******************
file: linklist.c
*******************
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/LineParser.h"
#include "../include/pipeline.h"
#include "../include/utils.h"

int **create_pipes(int n) {
    int **pipes = (int**)malloc(sizeof(int*) * n);
    int i;
    for(i = 0; i < n; i++) {
        int* pipefd = (int*)malloc(sizeof(int) * 2);
        if(pipe(pipefd) == -1) {
            print_error_msg("pipe", NULL);
            exit(EXIT_FAILURE);
        }
        pipes[i] = pipefd;
    }
    return pipes;
}

void release_pipes(int **pipes, int n) {
    int i;
    for(i = 0; i < n; i++)
        free(pipes[i]);
    free(pipes);
}

int *left_pipe(int **pipes, cmdLine* pCmdLine) {
    int* pipe = NULL;
    int idx = pCmdLine->idx;
    if(idx > 0)
        pipe = pipes[idx - 1];
    return pipe;
}

int *right_pipe(int **pipes, cmdLine* pCmdLine) {
    int* pipe = NULL;
    int idx = pCmdLine->idx;
    if(pCmdLine->next != NULL)
        pipe = pipes[idx];
    return pipe;
}
