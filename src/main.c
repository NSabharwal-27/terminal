#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "queue.h"

#define clear() system("clear")
#define INPUT_MAX 100

queue q;

void call_init() {
    clear();
    printf("Welcome to my shell!\n");
    printf("Use this shell at your own risk!!\n\n");
    q_init(&q);
}

// TODO if strlen buff == 0 ? flag = 0 : flag = 1
// flag determines return value
int read_input(char *input) {
    char *buffer = (char*) malloc (strlen(input) + 1);
    strcpy(buffer, input);

    if (strlen(buffer) == 0) {
        free(buffer);
        return 0;
    }
    enqueue(&q, buffer);
    free(buffer);  // Free the buffer after adding to history
    return 1;
}

void execute(char *input) {
    char *args[INPUT_MAX];
    char *token;
    int i = 0;

    // Remove the trailing newline character
    input[strcspn(input, "\n")] = '\0';

    // Tokenize the input
    token = strtok(input, " ");
    while (token != NULL && i < INPUT_MAX - 1) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL; // Null-terminate the args array

    // Fork a child process
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // In child process
        execvp(args[0], args);
        // If execvp returns, it must have failed
        perror("execvp errored");
        exit(1);
    } else {
        // In parent process
        wait(NULL);
    }
}

int main() {
    char input[INPUT_MAX];
    char *username;
    call_init();

    username = getlogin();
    do {
        printf("%s:>>", username);
        if (fgets(input, INPUT_MAX, stdin) == NULL) {
            perror("fgets failed");
            exit(1);
        }

        if (strcmp(input, "exit\n") == 0)
            break;

        if (read_input(input)) {
            if (strcmp(input, "history\n") == 0) {
                print_history(&q);
            } else {
                execute(input);
            }
        }
    } while (1);
    return 0;
}