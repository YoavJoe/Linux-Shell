
#include "../include/myshell.h"

int execute(cmdLine *pCmdLine) {
    int ret; 
    char* commend = (pCmdLine->arguments)[0];
    fork();
    ret = execvp(commend, pCmdLine->arguments);

    if(ret == -1) {
        perror("Error: ");
        _exit(1);
    }

    freeCmdLines(pCmdLine);

    return EXIT_SUCCESS;

}