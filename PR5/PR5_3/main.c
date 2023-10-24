#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int signo) {
    static int count = 0;
    printf("Handler %d: Termination signal %d received\n", count + 1, signo);
    count++;
    sleep(1);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number of handlers>\n", argv[0]);
        return 1;
    }

    int num_handlers = atoi(argv[1]);

    if (num_handlers <= 0) {
        fprintf(stderr, "The number of handlers should be greater than 0\n");
        return 1;
    }

    for (int i = 0; i < num_handlers; i++) {
        if (signal(SIGINT, signal_handler) == SIG_ERR) {
            perror("Error setting up the handler");
            return 1;
        }
    }

    printf("The program is ready to handle %d termination signals.\n", num_handlers);

    while (1) {

    }

    return 0;
}
