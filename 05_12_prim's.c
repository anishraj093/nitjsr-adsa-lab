#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 5  // number of vertices

// Find vertex with minimum key value from unvisited set
int minKey(int key[], bool inMST[]) {
    int min = INT_MAX, min_index = -1;
    int v;
    for ( v = 0; v < V; v++) {
        if (!inMST[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

// Print the constructed MST
void printMST(int parent[], int graph[V][V]) {
    printf("Edge \tWeight\n");
    int i;
    for ( i = 1; i < V; i++)
        printf("%d - %d \t%d\n", parent[i], i, graph[i][parent[i]]);
}

// Prim’s algorithm
void primMST(int graph[V][V]) {
    int parent[V];   // store constructed MST
    int key[V];      // minimum weight edge for each vertex
    bool inMST[V];   // track included vertices

    // Initialize keys
    int i;
    for ( i = 0; i < V; i++) {
        key[i] = INT_MAX;
        inMST[i] = false;
    }
    key[0] = 0;      // start from vertex 0
    parent[0] = -1;  // root has no parent
	int count;
    for ( count = 0; count < V - 1; count++) {
        int u = minKey(key, inMST);
        inMST[u] = true;

        // Update key values of neighbors
        int v;
        for ( v = 0; v < V; v++) {
            if (graph[u][v] && !inMST[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printMST(parent, graph);
}

// Driver code
int main() {
    // Example graph (adjacency matrix)
    int graph[V][V] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

    primMST(graph);
    return 0;
}
