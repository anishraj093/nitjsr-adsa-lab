#include <stdio.h>

#define V 5  // number of vertices

// Hardcoded adjacency matrix
int graph[V][V] = {
    {0, 1, 0, 1, 0},
    {1, 0, 1, 0, 0},
    {0, 1, 0, 1, 0},
    {1, 0, 1, 0, 1},
    {0, 0, 0, 1, 0}
};

// Function to check if graph is bipartite using BFS
int isBipartite() {
    int color[V];
    for (int i = 0; i < V; i++)
        color[i] = -1;  // -1 means uncolored

    int queue[V], front, rear;

    for (int start = 0; start < V; start++) {
        if (color[start] == -1) {  // not yet colored
            front = rear = 0;
            queue[rear++] = start;
            color[start] = 0;  // assign first color

            while (front < rear) {
                int u = queue[front++];

                for (int v = 0; v < V; v++) {
                    if (graph[u][v]) {  // if edge exists
                        if (color[v] == -1) {
                            color[v] = 1 - color[u];
                            queue[rear++] = v;
                        } else if (color[v] == color[u]) {
                            return 0;  // same color → not bipartite
                        }
                    }
                }
            }
        }
    }
    return 1;  // bipartite
}

int main() {
    if (isBipartite())
        printf("The graph is Bipartite\n");
    else
        printf("The graph is NOT Bipartite\n");

    return 0;
}
