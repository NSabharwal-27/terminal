#ifndef QUEUE_H
#define QUEUE_H

#define INPUT_MAX 100

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

void q_init(queue *q);
int is_empty(queue *q);
int get_size(queue *q);
void enqueue(queue *q, char *buffer);
void print_history(queue *q);

#endif // QUEUE_H