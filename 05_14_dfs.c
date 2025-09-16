#include <stdio.h>
#include <stdlib.h>

#define V 5   // number of vertices (change as needed)

int graph[V][V] = {
    // Example directed graph (hardcoded adjacency matrix)
    // 0 -> 1, 0 -> 2, 1 -> 3, 2 -> 3, 3 -> 4
    {0, 1, 1, 0, 0},  // edges from vertex 0
    {0, 0, 0, 1, 0},  // edges from vertex 1
    {0, 0, 0, 1, 0},  // edges from vertex 2
    {0, 0, 0, 0, 1},  // edges from vertex 3
    {0, 0, 0, 0, 0}   // edges from vertex 4
};

int visited[V], discovery[V], finish[V];
int timeCounter = 0;

// DFS function
void DFS(int u) {
    visited[u] = 1;
    discovery[u] = ++timeCounter;
	int v;
    for ( v = 0; v < V; v++) {
        if (graph[u][v]) {
            if (visited[v] == 0) {
                printf("Tree Edge: %d -> %d\n", u, v);
                DFS(v);
            } 
            else if (visited[v] == 1) {
                printf("Back Edge: %d -> %d\n", u, v);
            } 
            else if (visited[v] == 2) {
                if (discovery[u] < discovery[v]) {
                    printf("Forward Edge: %d -> %d\n", u, v);
                } else {
                    printf("Cross Edge: %d -> %d\n", u, v);
                }
            }
        }
    }

    visited[u] = 2;
    finish[u] = ++timeCounter;
}

// Driver
int main() {
    // Initialize visited array
    int i;
    for (i = 0; i < V; i++) visited[i] = 0;

    printf("DFS Edge Classification:\n");
    for (i = 0; i < V; i++) {
        if (visited[i] == 0) {
            DFS(i);
        }
    }

    return 0;
}
