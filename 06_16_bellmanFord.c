#include <stdio.h>
#include <limits.h>

#define V 5   // number of vertices
#define E 8   // number of edges

// structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Bellman-Ford Algorithm
void BellmanFord(struct Edge edges[], int src) {
    int dist[V];

    // Step 1: Initialize distances
    int i,j;
    for ( i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[src] = 0;

    // Step 2: Relax all edges (V-1 times)
    for ( i = 1; i <= V - 1; i++) {
        for ( j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int w = edges[j].weight;

            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    // Step 3: Check for negative weight cycle
    for ( j = 0; j < E; j++) {
        int u = edges[j].src;
        int v = edges[j].dest;
        int w = edges[j].weight;

        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            printf("Graph contains negative weight cycle!\n");
            return;
        }
    }

    // Print result
    printf("Vertex Distance from Source %d:\n", src);
    for ( i = 0; i < V; i++) {
        if (dist[i] == INT_MAX)
            printf("%d \t INF\n", i);
        else
            printf("%d \t %d\n", i, dist[i]);
    }
}

// Driver code
int main() {
    struct Edge edges[E] = {
        {0, 1, -1}, {0, 2, 4}, 
        {1, 2, 3}, {1, 3, 2}, 
        {1, 4, 2}, {3, 2, 5}, 
        {3, 1, 1}, {4, 3, -3}
    };

    BellmanFord(edges, 0); // source = 0

    return 0;
}
