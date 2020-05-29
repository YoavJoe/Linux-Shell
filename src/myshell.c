
#include "../include/myshell.h"

extern char* prg_name;

void print_directory() {
    char pwd[PATH_MAX];
    getcwd(pwd, PATH_MAX);

    printf(BOLD_BLUE "%s" RESET "$ ", pwd + 1);
}

void print_error_msg(char* commend, char* msg) {
    if(msg == NULL) {
        fprintf(stderr, "In " BOLD_GREEN "%s" RESET ": %s:" BOLD_RED " %s... fix it right now!!\n" RESET, prg_name, commend, strerror(errno));
    }
    else {
        fprintf(stderr, "In " BOLD_GREEN "%s" RESET ": %s:" BOLD_RED " %s... fix it right now!!\n" RESET, prg_name, commend, msg);
    }
}

int is_added_commend(char* cmd) {
    if(strncmp(cmd, "cd", 2) == 0)
        return TRUE;
    return FALSE;
}

int execute(cmdLine *pCmdLine) {
    int ret; 
    char* commend = (pCmdLine->arguments)[0];
    ret = execvp(commend, pCmdLine->arguments);

    if(ret == -1) {
        perror("Error: ");
        _exit(1);
    }

    freeCmdLines(pCmdLine);

    return EXIT_SUCCESS;

}

int change_directory(char* path) {
    int ret; /*for debuging*/

    if(strcmp(path, "~") == 0) {
        path = getenv("HOME");
    }

    ret = chdir(path);
    return ret;
}