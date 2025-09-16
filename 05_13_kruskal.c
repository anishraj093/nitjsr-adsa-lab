#include <stdio.h>
#include <stdlib.h>

#define V 4   // number of vertices

// Edge structure
typedef struct {
    int src, dest, weight;
} Edge;

// Compare edges by weight (for qsort)
int compare(const void* a, const void* b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

// Find function
int find(int parent[], int i) {
    while (parent[i] != i)
        i = parent[i];
    return i;
}

// Union function
void unionSet(int parent[], int u, int v) {
    int uroot = find(parent, u);
    int vroot = find(parent, v);
    parent[uroot] = vroot;
}

// Kruskal’s MST
void KruskalMST(int graph[V][V]) {
    Edge edges[V*V];
    int E = 0;

    // Convert adjacency matrix to edge list
    int i,j;
    for ( i = 0; i < V; i++) {
        for ( j = i+1; j < V; j++) {  // i+1 to avoid duplicate edges
            if (graph[i][j] != 0) {
                edges[E].src = i;
                edges[E].dest = j;
                edges[E].weight = graph[i][j];
                E++;
            }
        }
    }

    // Sort edges by weight
    qsort(edges, E, sizeof(Edge), compare);

    int parent[V];
    for (i = 0; i < V; i++) parent[i] = i;

    printf("Edges in the Minimum Spanning Tree:\n");
    int count = 0;
    for ( i = 0; i < E && count < V - 1; i++) {
        int u = edges[i].src;
        int v = edges[i].dest;

        int setU = find(parent, u);
        int setV = find(parent, v);

        if (setU != setV) {
            printf("%d -- %d == %d\n", u, v, edges[i].weight);
            unionSet(parent, setU, setV);
            count++;
        }
    }
}

int main() {
    //adjacency matrix
    int graph[V][V] = {
        {0, 10, 6, 5},
        {10, 0, 0, 15},
        {6, 0, 0, 4},
        {5, 15, 4, 0}
    };

    KruskalMST(graph);
    return 0;
}
