#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

void execute_command(const char *command) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        execlp(command, command, (char *)NULL);
        perror("exec failed");
        exit(EXIT_FAILURE);
    } else {
        wait(NULL);
    }
}

int main() {
    char input[MAX_INPUT_SIZE];

    while (1) {
        printf("SimpleShell> ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        input[strcspn(input, "\n")] = '\0';

        if (strlen(input) == 0) {
            continue;
        }

        execute_command(input);
    }

    printf("\nGoodbye!\n");
    return 0;
}
