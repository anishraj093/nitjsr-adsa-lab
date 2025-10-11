#include <stdio.h>

#define V 5  // number of vertices 

// Hardcoded adjacency matrix
int graph[V][V] = {
    {0, 1, 1, 0, 1},
    {1, 0, 1, 1, 0},
    {1, 1, 0, 1, 0},
    {0, 1, 1, 0, 1},
    {1, 0, 0, 1, 0}
};

int path[V];

// Check if vertex v can be added to path[pos]
int isSafe(int v, int pos) {
    // Check adjacency
    if (graph[path[pos - 1]][v] == 0)
        return 0;

    // Check if already included
    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return 0;

    return 1;
}

// Recursive function to find Hamiltonian Cycle
int hamCycleUtil(int pos) {
    // Base case: if all vertices are in path
    if (pos == V) {
        // Check if last vertex connects to first
        if (graph[path[pos - 1]][path[0]] == 1)
            return 1;
        else
            return 0;
    }

    // Try different vertices as next candidate
    for (int v = 1; v < V; v++) {
        if (isSafe(v, pos)) {
            path[pos] = v;

            if (hamCycleUtil(pos + 1))
                return 1;

            // backtrack
            path[pos] = -1;
        }
    }
    return 0;
}

// Solve the Hamiltonian Cycle problem
int hamCycle() {
    for (int i = 0; i < V; i++)
        path[i] = -1;

    path[0] = 0;  // start from vertex 0

    if (hamCycleUtil(1) == 0) {
        printf("No Hamiltonian Cycle found\n");
        return 0;
    }

    printf("Hamiltonian Cycle exists: ");
    for (int i = 0; i < V; i++)
        printf("%d ", path[i]);
    printf("%d\n", path[0]);  // complete the cycle

    return 1;
}

// Main function
int main() {
    hamCycle();
    return 0;
}
