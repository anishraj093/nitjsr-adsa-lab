#include <stdio.h>
#include <limits.h>
#include <stdbool.h>



// Find vertex with minimum distance value from unvisited set
int minDistance(int dist[], bool visited[],int vertices) {
    int min = INT_MAX, min_index = -1;
    int v;
    for (v = 0; v < vertices; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Print shortest distances
void printSolution(int dist[],int vertices) {
    printf("Vertex \t Distance from Source\n");
    int i;
    for (i = 0; i < vertices; i++)
        printf("%d \t %d\n", i, dist[i]);
}

// Dijkstra algorithm
void dijkstra(int vertices,int graph[vertices][vertices], int src) {
    int dist[vertices];      // dist[i] = shortest distance from src to i
    bool visited[vertices];  // visited[i] = true if vertex processed

    // Initialize distances
    int i;
    for ( i = 0; i < vertices; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }
    dist[src] = 0;

    // Find shortest path for all vertices
    int count;
    for (count = 0; count < vertices - 1; count++) {
        int u = minDistance(dist, visited,vertices);
        visited[u] = true;

        // Update dist[v]
        int v;
        for ( v = 0; v < vertices; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printSolution(dist,vertices);
}

// Driver code
int main() {
    // Example graph (adjacency matrix)
    int v;
    printf("Enter the vertex: ");
    scanf("%d",&v);
    
//    int graph[V][V] = {
//        {0, 10, 0, 0, 5},
//        {0, 0, 1, 0, 2},
//        {0, 0, 0, 4, 0},
//        {7, 0, 6, 0, 0},
//        {0, 3, 9, 2, 0}
//    };
	int graph[v][v];
	int a,b;
	for(a=0;a<v;a++){
		for(b=0;b<v;b++){
			graph[a][b]=0;
		}
	}
	int i,j;
	for(i=0;i<v-1;i++){
		for(j=i+1;j<v;j++){
			printf("enter the weight of %d %d: ",i,j);
			int w;
			scanf("%d",&w);
			graph[i][j]=w;
			graph[j][i]=w;
		}
	}
	

    dijkstra(v,graph, 0); // source = vertex 0
    return 0;
}
