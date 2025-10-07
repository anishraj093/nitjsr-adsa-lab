#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int graph[MAX][MAX]; 
int visited[MAX], stack[MAX], top = -1;

// DFS for topological sort
void topoDFS(int v, int V) {
    visited[v] = 1;
    int i;
    for ( i = 0; i < V; i++) {
        if (graph[v][i] && !visited[i]) {
            topoDFS(i, V);
        }
    }
    stack[++top] = v;  // push to stack after visiting all neighbors
}

// Function to perform topological sort
void topologicalSort(int V) {
	int i;
    for ( i = 0; i < V; i++)
        visited[i] = 0;

    for ( i = 0; i < V; i++)
        if (!visited[i])
            topoDFS(i, V);

    printf("Topological Order: ");
    while (top >= 0) {
        printf("%d ", stack[top--]);
    }
    printf("\n");
}

// Driver
int main() {
    int V, E;
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    // initialize adjacency matrix
    int i,j;
    for ( i = 0; i < V; i++)
        for ( j = 0; j < V; j++)
            graph[i][j] = 0;

    printf("Enter edges (u v) (u->v directed):\n");
    for ( i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
    }

    topologicalSort(V);

    return 0;
}

