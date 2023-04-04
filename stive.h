#pragma once

#include <limits.h>

#include "list.h"

typedef Team StackData;

typedef struct StackNode {
    StackData *val;
    struct StackNode *next;
} StackNode;

StackData *top(StackNode *top);
void push(StackNode**top, StackData *v);
StackData *pop(StackNode**top);
int isStackEmpty(StackNode*top);
void deleteStack(StackNode**top);
void functiebelea(StackNode *stackCopy, FILE *file);
