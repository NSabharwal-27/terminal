#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

void execute(char *input){
    printf("tehe we working\n");
}

int main() {
    char input[INPUT_MAX];
    char *username;
    call_init();

    username = getlogin();
    do {
        printf("%s:>>", username);
        fgets(input, INPUT_MAX, stdin);
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