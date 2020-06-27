/*
*******************
file: myshell.c
*******************
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h> /*for fork*/
#include <sys/wait.h>
#include <unistd.h>
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

void check_internal_environment(cmdLine* parsedLine) {
    char* arg = NULL, *value = NULL;
    int i;
    for(i = 1; i < parsedLine->argCount; i++) {
        if(is_environment_empty())
            return;
        arg = parsedLine->arguments[i];
        if(arg[0] == '$') {
            value = find_value(arg + 1);
        if(value == NULL)
            print_error_msg("$", "not exist");
        else
            replaceCmdArg(parsedLine, i, value);
        }
    }
}

void execute_added_command(cmdLine* cmd) {
    char* command = cmd->arguments[0];
    if(strcmp(command, "cd") == 0)
        change_directory(cmd->arguments[1]);
    else if(strcmp(command, "history") == 0)
        print_history();
    else if(strcmp(command, "set") == 0) 
        add_to_environment(cmd->arguments[1], cmd->arguments[2]);
    else if(strcmp(command, "env") == 0)
        print_environment();
    else if(strcmp(command, "delete") == 0)
        delete_from_environment(cmd->arguments[1]);
}

int main(int argc, char** argv) {
    cmdLine *parsedLine = NULL;
    pid_t pid;
    int status = 0;
    int has_history = FALSE; /*flag for build link list for history*/
    char input[PATH_MAX] = "";
    char* selected_command;
    int location = 0;
    int pip[2];
    int reader, writer;
    
    prg_name = argv[0] + 2; /*pass over ./ */

    while(1) {
        print_directory();

        fgets(input, PATH_MAX, stdin); /*get the commend from the user*/

        if(strcmp(input, "\n") == 0)
            continue;

        if(strcmp(input, "quit\n") == 0) /*end of the infinite loop of the shell if the command "quit" is enterd */
            break;

        if(input[0] == '!') { /* Eli: input[0] == '!' */
            if(is_number(input + 1))
                location = atoi(input + 1); /* atoi(input+1) if (input+1) is integer;*/
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
        check_internal_environment(parsedLine);

        if(is_added_command(input)) {
            execute_added_command(parsedLine);
            freeCmdLines(parsedLine);
            continue;
        }
        if(pipe(pip) == -1)
            print_error_msg("pipe", NULL);
        
        
        freeCmdLines(parsedLine);
    }

    free_environment();

    /*if there no commend so no need to free 
    list that haven't been allocated*/
    if(has_history == TRUE) 
        free_history();
    return EXIT_SUCCESS;
}