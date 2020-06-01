/*
*******************
file: myshell.c
*******************
*/
#include "../include/myshell.h"

int execute(cmdLine *pCmdLine) {
    int ret;
    char *commend = (pCmdLine->arguments)[0];
    ret = execvp(commend, pCmdLine->arguments);

    if (ret == -1){
        perror("Error: ");
        _exit(1);
    }

    freeCmdLines(pCmdLine);

    return EXIT_SUCCESS;
}

int change_directory(char *path) {
    int ret; /*for debuging*/

    if (strcmp(path, "~") == 0)
        path = getenv("HOME");

    ret = chdir(path);
    if (ret == -1)
        print_error_msg("cd", NULL);
    return ret;
}

int main(int argc, char** argv) {
    cmdLine *parsedLine = NULL;
    pid_t child_pid;
    int status = 0;
    int select_history = FALSE; /*flag for build link list for history*/
    char input[PATH_MAX] = "";
    
    prg_name = argv[0] + 2; /*pass over ./ */

    while(1) {
        print_directory();

        fgets(input, PATH_MAX, stdin); /*get the commend from the user*/

        if(strcmp(input, "quit\n") == 0) /*end of the infinite loop of the shell if the command "quit" is enterd */
            break;

        
        add_to_history(input);
        parsedLine = parseCmdLines(input);

        if(is_added_command(input)) {
            if(strncmp(input, "cd", 2) == 0)
                change_directory(parsedLine->arguments[1]);
            else if(strcmp(input, "history\n") == 0) {
                list_print();
                select_history = TRUE;
            }
            freeCmdLines(parsedLine);
            continue;
        }

        child_pid = fork(); /*create a child process*/
        
        if(child_pid == 0) { /*the child born successfuly, so start work with him*/
            execute(parsedLine);
        }
        else {
            waitpid(-1, &status, 0); /*the main process wait's for his child's to end*/
        }

        freeCmdLines(parsedLine);
    }
    /*if there no commend so no need to free 
    list that haven't been allocated*/
    if(select_history == TRUE) 
        free_list();

    return EXIT_SUCCESS;
}