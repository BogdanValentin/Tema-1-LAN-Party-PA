#include "../headers/tree.h"

int nodeHeight(AVLNode *node) {
    if(node == NULL) {
        return -1;
    } else {
        return node->height;
    }
}

BSTNode *BST_newNode(Team *data) {
    BSTNode *newNode = malloc(sizeof(BSTNode));
    if (newNode == NULL) {
		mallocError();
	}
    newNode->val = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

BSTNode *BST_insert(BSTNode *root, Team *team) {
    if(root == NULL) {
        return BST_newNode(team);
    }
    float score = findTeamScore(team);
    float rootScore = findTeamScore(root->val);
    if(score < rootScore) {
        root->left = BST_insert(root->left, team);
    } else if(score > rootScore) {
        root->right = BST_insert(root->right, team);
    } else { // egale
        if(strcmp(team->name, root->val->name) > 0) {
            root->right = BST_insert(root->right, team);
        } else if(strcmp(team->name, root->val->name) <  0){
            root->left = BST_insert(root->left, team);
        }
    }
    return root;
}

void BST_DRS(TeamList **list, BSTNode *root, char *fileNameOutput) {
    if(root) {
        BST_DRS(list, root->right, fileNameOutput);
        FILE *file = fopen(fileNameOutput, "at");
        if(file) {
            fprintf(file, "%-34s-  %.2f\n", root->val->name, findTeamScore(root->val));
            addTeamToBeginningOfTeamList(list, root->val);
            fclose(file);
        }
        BST_DRS(list, root->left, fileNameOutput);
    }
}

void AVL_DRS(AVLNode *root, char *fileNameOutput, int level) {
    if(root) {
        level++;
        AVL_DRS(root->right, fileNameOutput, level);
        FILE *file = fopen(fileNameOutput, "at");
        if(file) {
            if(level == 2) {
                fprintf(file, "%s\n", root->val->name);
            }
            fclose(file);
        }
        AVL_DRS(root->left, fileNameOutput, level);
    }
}

AVLNode *rightRotation(AVLNode *z) {
    AVLNode *y = z->left;
    AVLNode *T3 = y->right;

    y->right = z;
    z->left = T3;

    z->height = max(nodeHeight(z->left), nodeHeight(z->right)) + 1;
    y->height = max(nodeHeight(y->left), nodeHeight(y->right)) + 1;
    return y;
}

AVLNode *leftRotation(AVLNode *z) {
    AVLNode *y = z->right;
    AVLNode *T2 = y->left;
    y->left = z;
    z->right = T2;
    z->height = max(nodeHeight(z->left), nodeHeight(z->right)) + 1;
    y->height = max(nodeHeight(y->left), nodeHeight(y->right)) + 1;
    return y;
}

AVLNode *LRRotation(AVLNode *z) {
    z->left = leftRotation(z->left);
    return rightRotation(z);
}

AVLNode *RLRotation(AVLNode *z) {
    z->right = rightRotation(z->right);
    return leftRotation(z);
}

AVLNode *createNode(Team *team) {
    AVLNode *node = malloc(sizeof(AVLNode));
    if (node == NULL) {
        mallocError();
    }
    node->val = team;
    node->height = 0;
    node->left = node->right = NULL;
    return node;
}

void updateChildrenScore(float *scoreOfLeftChild, float *scoreOfRightChild, AVLNode *node) {
    if (node->left != NULL) {
        *scoreOfLeftChild = findTeamScore(node->left->val);
    } else {
        *scoreOfLeftChild = 0;
    }
    if (node->right != NULL) {
        *scoreOfRightChild = findTeamScore(node->right->val);
    } else {
        *scoreOfRightChild = 0;
    }
}

void decideRotation(AVLNode **nodePtr, int k, float scoreOfTeam, float scoreOfLeftChild, float scoreOfRightChild, Team *team) {
    AVLNode *node = *nodePtr;
    if (k > 1) {
        if (scoreOfTeam < scoreOfLeftChild) {
            *nodePtr = rightRotation(node);
        } else if (scoreOfTeam == scoreOfLeftChild) {
            if (strcmp(node->left->val->name, team->name) > 0) {
                *nodePtr = rightRotation(node);
            }
        }
    } else if (k < -1) {
        if (scoreOfTeam > scoreOfRightChild) {
            *nodePtr = leftRotation(node);
        } else if (scoreOfTeam == scoreOfRightChild) {
            if (strcmp(node->right->val->name, team->name) < 0) {
                *nodePtr = leftRotation(node);
            }
        }
    } else if (k > 1 && scoreOfTeam > scoreOfLeftChild) {
        *nodePtr = RLRotation(node);
    } else if (k < -1 && scoreOfTeam < scoreOfRightChild) {
        *nodePtr = LRRotation(node);
    }
}

AVLNode *AVL_insert(AVLNode *node, Team *team) {
    if (node == NULL) {
        return createNode(team);
    }

    float scoreOfNode = findTeamScore(node->val);
    float scoreOfTeam = findTeamScore(team);

    if (scoreOfTeam < scoreOfNode) {
        node->left = AVL_insert(node->left, team);
    } else if (scoreOfTeam > scoreOfNode) {
        node->right = AVL_insert(node->right, team);
    } else {
        if (strcmp(node->val->name, team->name) > 0) {
            node->left = AVL_insert(node->left, team);
        } else if (strcmp(node->val->name, team->name) < 0) {
            node->right = AVL_insert(node->right, team);
        }
    }

    node->height = 1 + max(nodeHeight(node->left), nodeHeight(node->right));
    int k = nodeHeight(node->left) - nodeHeight(node->right);

    float scoreOfLeftChild, scoreOfRightChild;
    updateChildrenScore(&scoreOfLeftChild, &scoreOfRightChild, node);

    decideRotation(&node, k, scoreOfTeam, scoreOfLeftChild, scoreOfRightChild, team);

    return node;
}

void createBSTTree(BSTNode **root, TeamList *last8Finalists) {
    while(last8Finalists != NULL) {
        *root = BST_insert(*root, last8Finalists->team);
        last8Finalists = last8Finalists->next;
    }
}

void deleteBSTTree(BSTNode *root) {
    if(root) {
        deleteBSTTree(root->left);
        deleteBSTTree(root->right);
        free(root);
    }
}

void deleteAVLTree(AVLNode *root) {
    if(root) {
        deleteAVLTree(root->left);
        deleteAVLTree(root->right);
        free(root);
    }
}
