#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s \"command1; command2; ...\"\n", argv[0]);
        return 1;
    }

    char *commands = argv[1];

    char *command = strtok(commands, ";");
    while (command != NULL) {
        int exit_status = system(command);

        printf("Command: %s\n", command);
        printf("Exit Status: %d\n", exit_status);

        command = strtok(NULL, ";");
    }

    return 0;
}
