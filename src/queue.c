#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

void q_init(queue *q) {
    q->count = 0;
    q->head = NULL;
    q->tail = NULL;
}

int is_empty(queue *q) {
    return q->tail == NULL;
}

int get_size(queue *q) {
    return q->count;
}

void enqueue(queue *q, char *buffer) {
    node *tmp = (node*)malloc(sizeof(node));
    tmp->next = NULL;
    strcpy(tmp->cmd, buffer);
    if (is_empty(q)) {
        q->head = q->tail = tmp;
    } else {
        q->tail->next = tmp;
        q->tail = tmp;
    }
    q->count++;
}

void print_history(queue *q) {
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