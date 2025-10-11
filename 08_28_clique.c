#include <stdio.h>

#define N 5  // number of vertices


int graph[N][N] = {
    {0, 1, 1, 0, 0},
    {1, 0, 1, 1, 0},
    {1, 1, 0, 1, 0},
    {0, 1, 1, 0, 1},
    {0, 0, 0, 1, 0}
};

int m = 3;  // size of clique to check (change as needed)

// Function to check if all vertices in subset form a clique
int isClique(int subset[], int size) {
	int i,j;
    for ( i = 0; i < size; i++) {
        for ( j = i + 1; j < size; j++) {
            if (graph[subset[i]][subset[j]] == 0)
                return 0; // not connected
        }
    }
    return 1;
}

// Recursive function to find clique of size m
int findClique(int index, int subset[], int size, int start) {
	int i;
    if (size == m) {
        if (isClique(subset, m)) {
            printf("Clique of size %d found: ", m);
            for ( i = 0; i < m; i++)
                printf("%d ", subset[i]);
            printf("\n");
            return 1;
        }
        return 0;
    }

    for ( i = start; i < N; i++) {
        subset[index] = i;
        if (findClique(index + 1, subset, size + 1, i + 1))
            return 1;
    }
    return 0;
}

int main() {
    int subset[N];
    if (!findClique(0, subset, 0, 0))
        printf("No clique of size %d found\n", m);
    return 0;
}

