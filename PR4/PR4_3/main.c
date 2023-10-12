#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
    if (argc == 2) {
        int result = unsetenv(argv[1]);
        if (result == -1) {
            printf("Error unsetting variable from environment.\n");
            return 1;
        }
    } else {
        int result = clearenv();
        if (result == -1) {
            printf("Error clearing environment.\n");
            return 1;
        }
    }

    extern char **environ;
    char **env = environ;
    while (*env != NULL) {
        printf("%s\n", *env);
        env++;
    }
    return 0;
}
