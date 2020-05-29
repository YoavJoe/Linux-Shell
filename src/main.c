#include "../include/myshell.h"

char* prg_name;

int main(int argc, char** argv) {
    cmdLine *parsedLine = NULL;
    pid_t child_pid;
    int status = 0;
    char input[PATH_MAX] = "";

    prg_name = argv[0] + 2; /*pass over ./ */

    while(1) {

        print_directory();
        fgets(input, PATH_MAX, stdin); /*get the commend from the user*/

        if(strcmp(input, "quit\n") == 0) /*end of the infinite loop of the shell if the commend "quit" is enterd */
            break;

        parsedLine = parseCmdLines(input);
        if(is_added_commend(input)) {
            if(change_directory(parsedLine->arguments[1]) == -1)
                print_error_msg("cd", NULL);


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

    return EXIT_SUCCESS;
}