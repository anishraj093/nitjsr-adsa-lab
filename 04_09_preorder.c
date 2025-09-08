#include <stdio.h>
#include <stdlib.h>

// Define tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Create a new node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Preorder traversal without recursion
void preorder(struct Node* root) {
    if (root == NULL) return;

    // Stack implemented as array of node pointers
    struct Node* stack[100];
    int top = -1;

    // Push root
    stack[++top] = root;

    while (top != -1) {
        // Pop and print
        struct Node* curr = stack[top--];
        printf("%d ", curr->data);

        // Push right first (so left is processed first)
        if (curr->right != NULL)
            stack[++top] = curr->right;

        if (curr->left != NULL)
            stack[++top] = curr->left;
    }
}
int main() {
    
    struct Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);
    root->right->right = newNode(7);

    printf("Preorder traversal (with recursion): ");
    preorder(root);

    return 0;
}
