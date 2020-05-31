
#include "../include/myshell.h"

extern char* prg_name;
extern list* head; /* listed list start */
extern list* last;

void init_history() {
    int i;
    history_arr = (char**)malloc(CAPACITY* sizeof(char*));
    for(i = 0; i < CAPACITY; i++)
        history_arr[i] = (char*)malloc(MAX_COMMAND_LENGTH* sizeof(char));
}

void free_history() {
    int i;
    for(i = 0; i< CAPACITY; i++)
        free(history_arr[i]);
    free(history_arr);
}

void add_to_history(char* cmd, int lastcmd) {
    if(lastcmd < (CAPACITY - 1)) {
        strcpy(history_arr[lastcmd], cmd);
        lastcmd++;
    }
    else
        print_error_msg("history", "out of bounds index!");
}


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
    else if(strncmp(cmd, "history", 7) == 0)
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
    if(ret == -1) print_error_msg("cd", NULL);
    return ret;
}

list* make_list(char** cmd_arr, int len) {
    int i;
    list* new_link = NULL;

    for(i = 0; i < len; i++) {

        new_link = make_new_link(cmd_arr[i]);

        if (head == NULL) {
			head = list_append(head, new_link);
			last = head;
		}
	    else
		    last = list_append(last, new_link);
    }

    return head;
}