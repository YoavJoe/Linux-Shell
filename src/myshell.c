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
#include <fcntl.h>
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

int get_size(cmdLine* cmd) {
    int size = 1;
    cmdLine* curr = cmd;
    while(curr->next != NULL) {
        size++;
        curr = curr->next;
    }
    return size;
}

int main(int argc, char** argv) {
    cmdLine *parsedLine = NULL;
    cmdLine* curr = NULL;
    pid_t pid;
    int status = 0;
    int has_history = FALSE; /*flag for build link list for history*/
    char input[PATH_MAX] = "";
    char* selected_command;
    int location = 0;
    int** pipes = NULL;
    int* left_p = NULL, *right_p = NULL;
    int reader, writer;
    int size;
    
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
            input[0] = '\0';
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
        size = get_size(parsedLine);

        if(size > 1)
            pipes = create_pipes(size - 1);

        curr = parsedLine;

        while(curr != NULL) {
            if(pipes != NULL) {
                left_p = left_pipe(pipes, curr);
                right_p = right_pipe(pipes, curr);
            }

            pid = fork();
            if(pid < 0)
                print_error_msg("fork", NULL);
            else if(pid == 0) { /*I'm the child*/
                const char* input_r = curr->inputRedirect;
                const char* output_r = curr->outputRedirect;
                if(input_r != NULL) {
                    close(STDIN);
                    open(input_r, O_RDONLY);
                }
                if(output_r != NULL) {
                    close(STDOUT);
                    open(output_r, O_WRONLY | O_CREAT);
                }
                if(left_p != NULL) {
                    reader = left_p[0];
                    close(STDIN);
                    dup(reader);
                    close(reader);
                }
                if(right_p != NULL) {
                    writer = right_p[1];
                    close(STDOUT);
                    dup(writer);
                    close(writer);
                }
                execute(curr);
            }
            else { /*I'm the parent*/
                if(curr->blocking == 1)
                    waitpid(-1, &status, 0);
                if(left_p != NULL)
                    close(left_p[0]);
                if(right_p != NULL)
                    close(right_p[1]);
            }
            curr = curr->next;
            sleep(1);
        }
        if(pipes != NULL)
            release_pipes(pipes, size - 1);
        freeCmdLines(parsedLine);
    }

    free_environment();

    /*if there no commend so no need to free 
    list that haven't been allocated*/
    if(has_history == TRUE) 
        free_history();
    return EXIT_SUCCESS;
}