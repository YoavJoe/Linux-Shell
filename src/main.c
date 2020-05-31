#include "../include/myshell.h"

char* prg_name;

int main(int argc, char** argv) {
    cmdLine *parsedLine = NULL;
    pid_t child_pid;
    int status = 0, lastcmd = 0;
    int select_history = FALSE; /*flag for build link list for history*/
    char input[PATH_MAX] = "";
    list* history = NULL;
    

    prg_name = argv[0] + 2; /*pass over ./ */

    init_history();

    while(1) {
        print_directory();

        fgets(input, PATH_MAX, stdin); /*get the commend from the user*/

        if(strcmp(input, "quit\n") == 0) /*end of the infinite loop of the shell if the commend "quit" is enterd */
            break;
        
        parsedLine = parseCmdLines(input);
        if(is_added_commend(input)) {
            if(strncmp(input, "cd", 2) == 0) {
                change_directory(parsedLine->arguments[1]);
                add_to_history(input, lastcmd);
                lastcmd++;
            }
            else if(strcmp(input, "history\n") == 0) {
                history = make_list(history_arr, lastcmd);
                list_print(history);
                select_history = TRUE;
            }
            freeCmdLines(parsedLine);
            continue;
        }

        add_to_history(input, lastcmd);
        lastcmd++;

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
        free_list(history);

    free_history();

    return EXIT_SUCCESS;
}
