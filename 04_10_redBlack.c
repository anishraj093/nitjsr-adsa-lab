#include <stdio.h>
#include <stdlib.h>

enum Color { RED, BLACK };

typedef struct RBNode {
    int data;
    enum Color color;
    struct RBNode *left, *right, *parent;
} RBNode;

// ===== Helper: create node =====
RBNode* createNode(int data) {
    RBNode* node = (RBNode*)malloc(sizeof(RBNode));
    node->data = data;
    node->color = RED;  // new nodes start as RED
    node->left = node->right = node->parent = NULL;
    return node;
}

// ===== createTree =====
RBNode* createTree() { return NULL; }

// ===== Left rotate =====
RBNode* rotateLeft(RBNode* root, RBNode* x) {
    RBNode* y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
    return root;
}

// ===== Right rotate =====
RBNode* rotateRight(RBNode* root, RBNode* y) {
    RBNode* x = y->left;
    y->left = x->right;
    if (x->right) x->right->parent = y;
    x->parent = y->parent;
    if (!y->parent) root = x;
    else if (y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;
    x->right = y;
    y->parent = x;
    return root;
}

// ===== Fix violations after insert =====
RBNode* fixInsert(RBNode* root, RBNode* z) {
    while (z->parent && z->parent->color == RED) {
        RBNode* gp = z->parent->parent;
        if (z->parent == gp->left) {
            RBNode* y = gp->right; // uncle
            if (y && y->color == RED) { // case 1
                z->parent->color = BLACK;
                y->color = BLACK;
                gp->color = RED;
                z = gp;
            } else {
                if (z == z->parent->right) { // case 2
                    z = z->parent;
                    root = rotateLeft(root, z);
                }
                z->parent->color = BLACK; // case 3
                gp->color = RED;
                root = rotateRight(root, gp);
            }
        } else {
            RBNode* y = gp->left; // uncle
            if (y && y->color == RED) { // mirror case 1
                z->parent->color = BLACK;
                y->color = BLACK;
                gp->color = RED;
                z = gp;
            } else {
                if (z == z->parent->left) { // mirror case 2
                    z = z->parent;
                    root = rotateRight(root, z);
                }
                z->parent->color = BLACK; // mirror case 3
                gp->color = RED;
                root = rotateLeft(root, gp);
            }
        }
    }
    root->color = BLACK;
    return root;
}

// ===== insertItem =====
RBNode* insertItem(RBNode* root, int data) {
    RBNode* z = createNode(data);
    RBNode* y = NULL;
    RBNode* x = root;

    while (x) {  // normal BST insert
        y = x;
        if (data < x->data) x = x->left;
        else x = x->right;
    }
    z->parent = y;
    if (!y) root = z;
    else if (data < y->data) y->left = z;
    else y->right = z;

    return fixInsert(root, z);
}

// ===== searchItem =====
RBNode* searchItem(RBNode* root, int key) {
    if (!root || root->data == key) return root;
    if (key < root->data) return searchItem(root->left, key);
    return searchItem(root->right, key);
}

// ===== deleteTree =====
void deleteTree(RBNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

// ===== inorderTraversal =====
void inorder(RBNode* root) {
    if (!root) return;
    inorder(root->left);
    printf("%d(%s) ", root->data, root->color==RED?"R":"B");
    inorder(root->right);
}

// ===== main demo =====
int main() {
    RBNode* root = createTree();
    int vals[] = {10,20,30,15,25,5,1};
    int i;
    for (i=0;i<7;i++) root = insertItem(root, vals[i]);

    printf("Inorder traversal (key(color)): ");
    inorder(root); printf("\n");

    int k=15;
    printf("Search %d: %s\n", k, searchItem(root,k)?"FOUND":"NOT FOUND");

    deleteTree(root);
    return 0;
}
