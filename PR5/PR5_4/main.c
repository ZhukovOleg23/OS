#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DEFAULT_BUFFER_SIZE 127

void display_help() {
    printf("Simple Command Processor\n");
    printf("Available options:\n");
    printf("-h or --help: Show program usage help\n");
    printf("-b or --buffer <size>: Set the buffer size for commands\n");
}

void clear_screen_and_exit() {
    printf("Wait 3 seconds...\n");
    sleep(3);
    system("clear");
    exit(0);
}

int main(int argc, char *argv[]) {
    int buffer_size = DEFAULT_BUFFER_SIZE;

    if (argc > 1) {
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
            display_help();
            clear_screen_and_exit();
        } else if ((strcmp(argv[1], "-b") == 0 || strcmp(argv[1], "--buffer") == 0) && argc > 2) {
            buffer_size = atoi(argv[2]);
        }
    }

    char username[100];
    if (getlogin_r(username, sizeof(username)) != 0) {
        perror("Failed to get username");
        clear_screen_and_exit();
    }

    printf("User: %s\n", username);

    char *command = (char *)malloc(buffer_size);
    if (command == NULL) {
        perror("Memory allocation failed");
        clear_screen_and_exit();
    }

    while (1) {
        printf("[%s]$: ", username);
        fflush(stdout);

        if (fgets(command, buffer_size, stdin) == NULL) {
            perror("Failed to read command");
            break;
        }

        if (strcmp(command, "stop\n") == 0) {
            clear_screen_and_exit();
        } else {
            int status = system(command);
            if (status == -1) {
                perror("Command execution failed");
            } else {
                printf("Command executed with status: %d\n", status);
            }
        }
    }

    free(command);
    return 0;
}