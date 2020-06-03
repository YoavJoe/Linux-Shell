/*
*******************
file: utils.c
*******************
*/
#include <stdio.h>
#include <errno.h> /*for display an error msg*/
#include <unistd.h>
#include <string.h>
#include "../include/utils.h"

extern char* prg_name;

void print_directory() {
    char pwd[PATH_MAX] = "";
    getcwd(pwd, PATH_MAX);

    printf(BOLD_BLUE "%s" RESET "$ ", pwd + 1);
}

void print_error_msg(char *command, char *msg) {
    if (msg == NULL)
        fprintf(stderr, "%s: %s:" BOLD_RED " %s\n" RESET, prg_name, command, strerror(errno));
    else
        fprintf(stderr, "%s: %s:" BOLD_RED " %s\n" RESET, prg_name, command, msg);
}

int is_added_command(char *cmd) {
    if (strncmp(cmd, "cd", 2) == 0)
        return TRUE;
    else if (strncmp(cmd, "history", 7) == 0)
        return TRUE;
    else if(strncmp(cmd, "set", 3) == 0)
        return TRUE;
    else if(strcmp(cmd, "env\n") == 0)
        return TRUE;
    return FALSE;
}