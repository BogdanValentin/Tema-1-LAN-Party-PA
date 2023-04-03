#pragma once

#include <limits.h>
#include <stdlib.h>

#include "list.h"

typedef Match Data;

typedef struct QueueNode {
    Data *val;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    QueueNode *front, *rear;
} Queue;

Queue* createQueue();
void enQueue(Queue*q, Data *v);
Data *deQueue(Queue*q);
int isQueueEmpty(Queue*q);
void deleteQueue(Queue*q);

