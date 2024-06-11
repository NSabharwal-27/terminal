#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define clear() system("clear")
#define INPUT_MAX 100
#define HIST_MAX 15

struct node {
    char cmd[INPUT_MAX];
    struct node *next;
};
typedef struct node node;

struct queue {
    int count;
    node *head;
    node *tail;
};
typedef struct queue queue;

queue *q;

void q_init() {
    q = malloc(sizeof(queue));
    q->count = 0;
    q->head = NULL;
    q->tail = NULL;
}

int is_empty() {
    return q->tail == NULL;
}

int get_size() {
    return q->count;
}

void call_init() {
    clear();
    printf("Welcome to my shell!\n");
    printf("Use this shell at your own risk!!\n\n");
    q_init();
}

void enqueue(char *buffer) {
    node *tmp = (node*)malloc(sizeof(node));
    tmp->next = NULL;

    strcpy(tmp->cmd, buffer);
    if (is_empty()) {
        q->head = q->tail = tmp;
    } else {
        q->tail->next = tmp;
        q->tail = tmp;
    }
    q->count++;
}

void add_history(char *buffer) {
    enqueue(buffer);
}

void print_history() {
    node *tmp;

    if (q->count == 0)
        printf("History is empty!\n");
    else {
        tmp = q->head;
        while (tmp != NULL) {
            printf("%s", tmp->cmd);
            tmp = tmp->next;
        }
    }
}

int read_input(char *input) {
    char *buffer = (char*) malloc (strlen(input) + 1);
    strcpy(buffer, input);

    if (strlen(buffer) == 0) {
        free(buffer);
        return 0;
    }
    add_history(buffer);
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
                print_history();
            } else {
                execute(input);
            }
        }
    } while(1);
    return 0;
}
