#include "../include/myshell.h"

int main(int argc, char** argv) {
    int len;
    cmdLine *parsedLine = NULL;
    char input[100] = "";
    while(1) {

        printf(">>> ");
        fgets(input, 100, stdin);

        puts(input);

        len = strlen(input);
        printf("%d\n", len);

        if(strncmp(input, "quit", len) == 0) /*end of the infinite loop of the shell if the commend "quit" is enterd */
            return 0;
        parsedLine = parseCmdLines(input);
        execute(parsedLine);
    }

    return 0;
}
