#include <stdio.h>
#define V 4   // number of vertices

int graph[V][V] = {
    {0, 1, 1, 1},
    {1, 0, 1, 0},
    {1, 1, 0, 1},
    {1, 0, 1, 0}
};

int colors[V];  // color assigned to each vertex

// Check if assigning color c to vertex v is safe
int isSafe(int v, int c) {
	int i;
    for ( i = 0; i < V; i++) {
        if (graph[v][i] && colors[i] == c)
            return 0;
    }
    return 1;
}

// Recursive function to color the graph
int graphColoring(int m, int v) {
    if (v == V)  // all vertices colored
        return 1;
	int c;
    for ( c = 1; c <= m; c++) {
        if (isSafe(v, c)) {
            colors[v] = c;

            if (graphColoring(m, v + 1))
                return 1;

            colors[v] = 0;  // backtrack
        }
    }
    return 0;
}

// Print the solution
void printSolution(int m) {
    printf("Coloring of vertices:\n");
    int i;
    for ( i = 0; i < V; i++)
        printf("Vertex %d -> Color %d\n", i, colors[i]);
}

int main() {
    int m = 3;  // number of colors
    int i;
    for ( i = 0; i < V; i++) colors[i] = 0;

    if (graphColoring(m, 0))
        printSolution(m);
    else
        printf("No solution exists with %d colors\n", m);

    return 0;
}

