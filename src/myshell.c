/*
*******************
file: myshell.c
*******************
*/
#include "../include/myshell.h"

int last_command = 0; /*counter the amount of command's in list*/

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
    int has_history = FALSE; /*flag for build link list for history*/
    char input[PATH_MAX] = "", *selected_command;
    int location = 0;
    
    prg_name = argv[0] + 2; /*pass over ./ */

    while(1) {
        print_directory();

        fgets(input, PATH_MAX, stdin); /*get the commend from the user*/

        if(strcmp(input, "quit\n") == 0) /*end of the infinite loop of the shell if the command "quit" is enterd */
            break;

        if(strncmp(input, "!", 1) == 0) {
            location = atoi(memset(input, '0', 1));
            if(location > last_command) {
                print_error_msg("!", "non-existing log index is invoked");
                continue;
            }
            selected_command = get_command(location);
            strcpy(input, selected_command);
        }
        has_history = TRUE;
        add_to_history(input);
        last_command++;
        parsedLine = parseCmdLines(input);

        if(is_added_command(input)) {
            if(strncmp(input, "cd", 2) == 0)
                change_directory(parsedLine->arguments[1]);
            else if(strcmp(input, "history\n") == 0) {
                print_history();
            }
            else if(strncmp(input, "set", 3) == 0) 
                add_to_environment(parsedLine->arguments[1], parsedLine->arguments[2]);
            else if(strcmp(input, "env\n") == 0) {
                print_environment();
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

    free_environment();

    /*if there no commend so no need to free 
    list that haven't been allocated*/
    if(has_history == TRUE) 
        free_history();
    return EXIT_SUCCESS;
}