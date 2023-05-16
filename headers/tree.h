#pragma once

#include "calculate.h"

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

/*  Struct used to store a Binary Search Tree.*/
typedef struct BSTNode {
    Team *val;
    struct BSTNode *left, *right; 
} BSTNode;

/*  Struct used to store an AVL Tree.*/
typedef struct AVLNode {
    Team *val;
    int height;
    struct AVLNode *left, *right; 
} AVLNode;

/*  Calculates the height of a node in an AVL tree.*/
int nodeHeight(AVLNode *node);

/*  Allocates memory and initializes a new binary search tree node.*/
BSTNode *BST_newNode(Team *data);

/*  Inserts a new node with the given data into the binary search tree.*/
BSTNode *BST_insert(BSTNode *root, Team *team);

/*  Traverses the binary search tree in right-root-left order and writes
    the data to a file.*/
void BST_DRS(TeamList **list, BSTNode *root, char *fileNameOutput);

/*  Traverses the AVL tree and writes the data to a file if the current
    level is 2.*/
void AVL_DRS(AVLNode *root, char *fileNameOutput, int level);

/*  Performs a right rotation on the AVL tree.*/
AVLNode *rightRotation(AVLNode *z);

/*  Performs a left rotation on the AVL tree.*/
AVLNode *leftRotation(AVLNode *z);

/*  Performs a left-right rotation on the AVL tree.*/
AVLNode *LRRotation(AVLNode *z);

/*  Performs a right-left rotation on the AVL tree.*/
AVLNode *RLRotation(AVLNode *z);

/*  Creates a new node for the AVL tree.*/
AVLNode *createNode(Team *team);

/*  Updates the scores of the left and right child nodes of a given AVL node*/
void updateChildrenScore(float *scoreOfLeftChild, float *scoreOfRightChild, AVLNode *node);

/*  Decides which rotation to perform on the AVL tree.*/
void decideRotation(AVLNode **nodePtr, int k, float scoreOfTeam, float scoreOfLeftChild, float scoreOfRightChild, Team *team);

/*  Inserts a new node with the given data into the AVL tree and balances it.*/
AVLNode *AVL_insert(AVLNode *node, Team *team);

/*  Creates a binary search tree from the given list of teams.*/
void createBSTTree(BSTNode **root, TeamList *last8Finalists);

/*  Deletes a binary search tree and frees its memory.*/
void deleteBSTTree(BSTNode *root);

/*  Deletes an AVL tree and frees its memory.*/
void deleteAVLTree(AVLNode *root);