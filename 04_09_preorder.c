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

// Recursive Preorder Traversal
void preorder(struct Node* root) {
    if (root == NULL) return;

    printf("%d ", root->data);   // Visit root
    preorder(root->left);        // Traverse left
    preorder(root->right);       // Traverse right
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
