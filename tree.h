#pragma once

#include "list.h"
#include "calculate.h"

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

typedef struct BSTNode {
    Team *val;
    struct BSTNode *left, *right; 
} BSTNode;

typedef struct AVLNode {
    Team *val;
    int height;
    struct AVLNode *left, *right; 
} AVLNode;

int nodeHeight(AVLNode *node);
BSTNode *BST_newNode(Team *data);
BSTNode *BST_insert(BSTNode *root, Team *team);
void BST_DRS(BSTNode *root, char *fileNameOutput);
AVLNode *rightRotation(AVLNode *z);
AVLNode *leftRotation(AVLNode *z);
AVLNode *LRRotation(AVLNode *z);
AVLNode *RLRotation(AVLNode *z);
AVLNode *AVL_insert(AVLNode *node, Team *team);
