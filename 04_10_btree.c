#include <stdio.h>
#include <stdlib.h>

#define T 2   // Minimum degree

// ===== B-Tree Node =====
typedef struct BTreeNode {
    int keys[2*T - 1];             // keys
    struct BTreeNode* children[2*T]; // child pointers
    int n;                         // number of keys
    int leaf;                      // 1 if leaf, 0 if internal
} BTreeNode;

// ===== Helper: Create a new node =====
BTreeNode* createNode(int leaf) {
    BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->leaf = leaf;
    node->n = 0;
    for (int i = 0; i < 2*T; i++) node->children[i] = NULL;
    return node;
}

// ===== createTree =====
BTreeNode* createTree() {
    return createNode(1);  // start with an empty leaf root
}

// ===== searchItem =====
BTreeNode* searchItem(BTreeNode* root, int key) {
    int i = 0;
    while (i < root->n && key > root->keys[i]) i++;

    if (i < root->n && key == root->keys[i]) return root;

    if (root->leaf) return NULL;

    return searchItem(root->children[i], key);
}

// ===== Split Child =====
void splitChild(BTreeNode* parent, int i, BTreeNode* y) {
    BTreeNode* z = createNode(y->leaf);
    z->n = T - 1;

    // Copy last (T-1) keys of y into z
    for (int j = 0; j < T - 1; j++) z->keys[j] = y->keys[j + T];

    // Copy children if not leaf
    if (!y->leaf) {
        for (int j = 0; j < T; j++) z->children[j] = y->children[j + T];
    }

    y->n = T - 1;

    // Insert new child into parent
    for (int j = parent->n; j >= i + 1; j--) {
        parent->children[j + 1] = parent->children[j];
    }
    parent->children[i + 1] = z;

    // Move middle key up
    for (int j = parent->n - 1; j >= i; j--) {
        parent->keys[j + 1] = parent->keys[j];
    }
    parent->keys[i] = y->keys[T - 1];

    parent->n++;
}

// ===== Insert Non-Full =====
void insertNonFull(BTreeNode* node, int key) {
    int i = node->n - 1;

    if (node->leaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->n++;
    } else {
        while (i >= 0 && key < node->keys[i]) i--;

        if (node->children[i + 1]->n == 2*T - 1) {
            splitChild(node, i + 1, node->children[i + 1]);

            if (key > node->keys[i + 1]) i++;
        }
        insertNonFull(node->children[i + 1], key);
    }
}

// ===== insertItem =====
BTreeNode* insertItem(BTreeNode* root, int key) {
    if (root->n == 2*T - 1) { // root full
        BTreeNode* s = createNode(0);
        s->children[0] = root;
        splitChild(s, 0, root);
        int i = 0;
        if (key > s->keys[0]) i++;
        insertNonFull(s->children[i], key);
        return s;
    } else {
        insertNonFull(root, key);
        return root;
    }
}

// ===== deleteTree =====
void deleteTree(BTreeNode* root) {
    if (!root) return;
    if (!root->leaf) {
        for (int i = 0; i <= root->n; i++) {
            deleteTree(root->children[i]);
        }
    }
    free(root);
}

// ===== deleteItem (very simple: just ignores balancing for lab use) =====
BTreeNode* deleteItem(BTreeNode* root, int key) {
    // For lab simplicity, we only support deletion from leaves
    int i = 0;
    while (i < root->n && key > root->keys[i]) i++;

    if (i < root->n && key == root->keys[i]) {
        // if leaf node
        if (root->leaf) {
            for (int j = i; j < root->n - 1; j++)
                root->keys[j] = root->keys[j + 1];
            root->n--;
        } else {
            printf("Delete for internal node not implemented (lab simplification)\n");
        }
    } else if (!root->leaf) {
        root->children[i] = deleteItem(root->children[i], key);
    }
    return root;
}

// ===== Traversal =====
void traverse(BTreeNode* root) {
    if (!root) return;
    int i;
    for (i = 0; i < root->n; i++) {
        if (!root->leaf) traverse(root->children[i]);
        printf("%d ", root->keys[i]);
    }
    if (!root->leaf) traverse(root->children[i]);
}

// ===== Main Demo =====
int main() {
    BTreeNode* root = createTree();

    root = insertItem(root, 10);
    root = insertItem(root, 20);
    root = insertItem(root, 5);
    root = insertItem(root, 6);
    root = insertItem(root, 12);
    root = insertItem(root, 30);
    root = insertItem(root, 7);
    root = insertItem(root, 17);

    printf("B-Tree traversal: ");
    traverse(root);
    printf("\n");

    int k = 6;
    printf("Search %d: %s\n", k, searchItem(root, k) ? "FOUND" : "NOT FOUND");

    root = deleteItem(root, 6);
    printf("After deleting 6: ");
    traverse(root);
    printf("\n");

    deleteTree(root);
    return 0;
}
