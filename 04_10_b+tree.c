#include <stdio.h>
#include <stdlib.h>

#define ORDER 3  // B+ Tree order (max children)

typedef struct BPTreeNode {
    int keys[ORDER];                // keys
    struct BPTreeNode* children[ORDER+1]; // child pointers
    int n;                          // number of keys
    int leaf;                       // 1 = leaf, 0 = internal
    struct BPTreeNode* next;        // leaf link
} BPTreeNode;

// ===== Helper: create node =====
BPTreeNode* createNode(int leaf) {
    BPTreeNode* node = (BPTreeNode*)malloc(sizeof(BPTreeNode));
    node->n = 0; node->leaf = leaf; node->next = NULL;
    int i;
    for (i=0;i<ORDER+1;i++) node->children[i]=NULL;
    return node;
}

// ===== createTree =====
BPTreeNode* createTree() { return createNode(1); }

// ===== searchItem =====
int searchItem(BPTreeNode* root, int key) {
    int i=0;
    while (i<root->n && key>root->keys[i]) i++;
    if (root->leaf) {
        return (i<root->n && root->keys[i]==key);
    } else {
        return searchItem(root->children[i], key);
    }
}

// ===== split child =====
void splitChild(BPTreeNode* parent, int i) {
    BPTreeNode* y = parent->children[i];
    int mid = y->n/2;

    BPTreeNode* z = createNode(y->leaf);
    z->n = y->n - mid;
    int j;
    for (j=0;j<z->n;j++) z->keys[j] = y->keys[mid+j];
    if (!y->leaf) {
        for (j=0;j<=z->n;j++) z->children[j] = y->children[mid+j];
    }
    y->n = mid;

    for (j=parent->n;j>=i+1;j--) parent->children[j+1]=parent->children[j];
    parent->children[i+1]=z;

    for (j=parent->n-1;j>=i;j--) parent->keys[j+1]=parent->keys[j];
    parent->keys[i]=z->keys[0]; // promote smallest key in z
    parent->n++;

    if (y->leaf) {  // maintain leaf links
        z->next = y->next;
        y->next = z;
    }
}

// ===== insert non-full =====
void insertNonFull(BPTreeNode* node, int key) {
    int i = node->n-1;
    if (node->leaf) {
        while (i>=0 && key<node->keys[i]) { node->keys[i+1]=node->keys[i]; i--; }
        node->keys[i+1]=key; node->n++;
    } else {
        while (i>=0 && key<node->keys[i]) i--;
        i++;
        if (node->children[i]->n==ORDER) {
            splitChild(node,i);
            if (key>node->keys[i]) i++;
        }
        insertNonFull(node->children[i], key);
    }
}

// ===== insertItem =====
BPTreeNode* insertItem(BPTreeNode* root, int key) {
    if (root->n==ORDER) { // root full
        BPTreeNode* s = createNode(0);
        s->children[0]=root;
        splitChild(s,0);
        int i= (key>s->keys[0]);
        insertNonFull(s->children[i], key);
        return s;
    } else {
        insertNonFull(root,key);
        return root;
    }
}

// ===== deleteTree =====
void deleteTree(BPTreeNode* root) {
    if (!root) return;
    int i;
    if (!root->leaf) for (i=0;i<=root->n;i++) deleteTree(root->children[i]);
    free(root);
}

// ===== traversal (prints all leaf keys) =====
void traverseLeaves(BPTreeNode* root) {
    while (!root->leaf) root=root->children[0];
    int i;
    while (root) {
        for (i=0;i<root->n;i++) printf("%d ",root->keys[i]);
        root=root->next;
    }
    printf("\n");
}

// ===== main demo =====
int main() {
    BPTreeNode* root = createTree();
    int vals[]={10,20,5,6,12,30,7,17};
    int i;
    for ( i=0;i<8;i++) root=insertItem(root,vals[i]);

    printf("B+ Tree leaf traversal: ");
    traverseLeaves(root);

    int k=6;
    printf("Search %d: %s\n",k, searchItem(root,k)?"FOUND":"NOT FOUND");

    deleteTree(root);
    return 0;
}
