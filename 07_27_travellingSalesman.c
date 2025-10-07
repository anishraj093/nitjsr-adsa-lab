#include <stdio.h>
#include <limits.h>

#define N 4  // change this for different number of nodes

int tsp(int graph[N][N], int pos, int visited[], int count, int cost, int *ans) {
    if (count == N && graph[pos][0]) {  // all nodes visited, return to start
        if (cost + graph[pos][0] < *ans)
            *ans = cost + graph[pos][0];
        return *ans;
    }

    for (int i = 0; i < N; i++) {
        if (!visited[i] && graph[pos][i]) {
            visited[i] = 1;
            tsp(graph, i, visited, count + 1, cost + graph[pos][i], ans);
            visited[i] = 0;  // backtrack
        }
    }
    return *ans;
}

int main() {
    int graph[N][N] = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    int visited[N] = {0};
    visited[0] = 1;  // start from node 0
    int ans = INT_MAX;

    int minCost = tsp(graph, 0, visited, 1, 0, &ans);

    printf("Minimum cost of TSP tour: %d\n", minCost);

    return 0;
}
