#include <stdio.h>
#include <stdlib.h>

// ===== AVL Node =====
typedef struct Node {
    int key;
    int height;
    struct Node *left, *right;
} Node;

// ===== Helpers =====
static int max(int a, int b) { return a > b ? a : b; }
static int height(Node *n) { return n ? n->height : 0; }

static Node* newNode(int key) {
    Node *n = (Node*)malloc(sizeof(Node));
    n->key = key;
    n->left = n->right = NULL;
    n->height = 1; // new node is initially at height 1
    return n;
}

static int getBalance(Node *n) {
    return n ? height(n->left) - height(n->right) : 0;
}

static Node* rotateRight(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    // rotation
    x->right = y;
    y->left = T2;

    // update heights
    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x; // new root
}

static Node* rotateLeft(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    // rotation
    y->left = x;
    x->right = T2;

    // update heights
    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y; // new root
}

static Node* minValueNode(Node *root) {
    Node *curr = root;
    while (curr && curr->left) curr = curr->left;
    return curr;
}

// ===== API: createTree, deleteTree, insertItem, deleteItem, searchItem =====

// Creates an empty AVL tree (just returns NULL root)
Node* createTree() {
    return NULL;
}

// Frees all nodes
void deleteTree(Node *root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

// Insert key and return (possibly new) root
Node* insertItem(Node *root, int key) {
    // 1) Normal BST insert
    if (!root) return newNode(key);
    if (key < root->key) root->left = insertItem(root->left, key);
    else if (key > root->key) root->right = insertItem(root->right, key);
    else return root; // no duplicates (ignore)

    // 2) Update height
    root->height = 1 + max(height(root->left), height(root->right));

    // 3) Balance
    int bf = getBalance(root);

    // Case LL
    if (bf > 1 && key < root->left->key)
        return rotateRight(root);

    // Case RR
    if (bf < -1 && key > root->right->key)
        return rotateLeft(root);

    // Case LR
    if (bf > 1 && key > root->left->key) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Case RL
    if (bf < -1 && key < root->right->key) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Delete key and return (possibly new) root
Node* deleteItem(Node *root, int key) {
    if (!root) return NULL;

    // 1) Normal BST delete
    if (key < root->key)
        root->left = deleteItem(root->left, key);
    else if (key > root->key)
        root->right = deleteItem(root->right, key);
    else {
        // node with 0 or 1 child
        if (!root->left || !root->right) {
            Node *tmp = root->left ? root->left : root->right;
            if (!tmp) { // no child
                free(root);
                return NULL;
            } else { // one child
                *root = *tmp;
                free(tmp);
            }
        } else {
            // node with 2 children: get inorder successor
            Node *succ = minValueNode(root->right);
            root->key = succ->key;
            root->right = deleteItem(root->right, succ->key);
        }
    }

    // 2) If tree had only one node
    if (!root) return NULL;

    // 3) Update height
    root->height = 1 + max(height(root->left), height(root->right));

    // 4) Balance
    int bf = getBalance(root);

    // Case LL
    if (bf > 1 && getBalance(root->left) >= 0)
        return rotateRight(root);

    // Case LR
    if (bf > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Case RR
    if (bf < -1 && getBalance(root->right) <= 0)
        return rotateLeft(root);

    // Case RL
    if (bf < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Returns pointer to node with key (or NULL)
Node* searchItem(Node *root, int key) {
    while (root) {
        if (key < root->key) root = root->left;
        else if (key > root->key) root = root->right;
        else return root;
    }
    return NULL;
}

// ===== Simple demo =====
static void preorder(Node *root) {
    if (!root) return;
    printf("%d ", root->key);
    preorder(root->left);
    preorder(root->right);
}

int main() {
    Node *root = createTree();

    // Insert
    int a[] = {30, 20, 40, 10, 25, 50, 5};
    int i;
    for ( i = 0; i < (int)(sizeof(a)/sizeof(a[0])); ++i)
        root = insertItem(root, a[i]);

    printf("Preorder after inserts: ");
    preorder(root); printf("\n");

    // Search
    int k = 25;
    printf("Search %d: %s\n", k, searchItem(root, k) ? "FOUND" : "NOT FOUND");

    // Delete a few
    root = deleteItem(root, 30);
    root = deleteItem(root, 5);

    printf("Preorder after deletes: ");
    preorder(root); printf("\n");

    deleteTree(root);
    return 0;
}

