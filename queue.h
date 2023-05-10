#pragma once

#include <limits.h>
#include <stdlib.h>
#include "error_handling.h"

#include "list.h"

typedef struct QueueNode {
    Match *val;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    QueueNode *front, *rear;
} Queue;

/*  Creates an empty queue for storing matches.*/
Queue* createQueue();

/*  Adds a match to the rear of a given queue.*/
void enQueue(Queue *q, Match *v);

/*  Removes and returns the match at the front of a given queue.*/
Match *deQueue(Queue *q);

/*  Checks whether a given queue is empty or not.*/
int isQueueEmpty(Queue *q);

/*  Deletes a given queue by freeing all allocated memory.*/
void deleteQueue(Queue *q);
