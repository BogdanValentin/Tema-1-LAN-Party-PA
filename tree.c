#include "tree.h"

int nodeHeight(AVLNode *node) {
    if(node == NULL) {
        return -1;
    } else {
        return node->height;
    }
}

BSTNode *BST_newNode(Team *data) {
    BSTNode *newNode = malloc(sizeof(BSTNode));
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

void BST_DRS(BSTNode *root, char *fileNameOutput) {
    if(root) {
        BST_DRS(root->right, fileNameOutput);
        FILE *file = fopen(fileNameOutput, "at");
        if(file) {
            fprintf(file, "%-34s-  %.2f\n", root->val->name, findTeamScore(root->val));
            fclose(file);
        }
        BST_DRS(root->left, fileNameOutput);
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

AVLNode *AVL_insert(AVLNode *node, Team *team) {
    float scoreOfNode = findTeamScore(node->val);
    float scoreOfTeam = findTeamScore(team);

    if(node == NULL) {
        node = malloc(sizeof(AVLNode));
        node->val = team;
        node->height = 0;
        node->left = node->right = NULL;
        return node;
    }
    if(scoreOfTeam < scoreOfNode) {
        node->left = AVL_insert(node->left, team);
    } else if(scoreOfTeam > scoreOfNode) {
        node->right = AVL_insert(node->right, team);
    } else return node;
    node->height = 1 + max(nodeHeight(node->left),nodeHeight(node->right));
    int k = nodeHeight(node->left) - nodeHeight(node->right);

    float scoreOfLeftChild = findTeamScore(node->left->val);
    float scoreOfRightChild = findTeamScore(node->right->val);

    if(k > 1 && scoreOfTeam < scoreOfLeftChild) {
        return rightRotation(node);
    }
    if(k < -1 && scoreOfTeam > scoreOfRightChild) {
        return leftRotation(node);
    }
    if(k > 1 && scoreOfTeam > scoreOfLeftChild) {
        return RLRotation(node);
    }
    if(k < -1 && scoreOfTeam < scoreOfRightChild) {
        return LRRotation(node);
    }
    return node;
}