#pragma once

#include <limits.h>

#include "list.h"

typedef Team StackData;

typedef struct StackNode {
    StackData *val;
    struct StackNode *next;
} StackNode;

/*  Returns the value at the top of the stack.*/
StackData *top(StackNode *top);

/*  Pushes a new value onto the stack.*/
void push(StackNode **top, StackData *v);

/*  Pops the value from the top of the stack.*/
StackData *pop(StackNode **top);

/*  Checks if the stack is empty.*/
int isStackEmpty(StackNode *top);

/*  Deletes the entire stack and frees its memory.*/
void deleteStack(StackNode **top);
