#include <stdio.h>
#define N 5   // change N for different board sizes

int board[N][N];

// Check if placing a queen at board[row][col] is safe
int isSafe(int row, int col) {
    int i, j;

    // Check this row on the left
    for (i = 0; i < col; i++)
        if (board[row][i]) return 0;

    // Check upper diagonal on the left
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j]) return 0;

    // Check lower diagonal on the left
    for (i = row, j = col; i < N && j >= 0; i++, j--)
        if (board[i][j]) return 0;

    return 1;
}

// Solve N-Queens using backtracking
int solveNQ(int col) {
    if (col >= N) return 1; // all queens placed
	int i;
    for (i = 0; i < N; i++) {
        if (isSafe(i, col)) {
            board[i][col] = 1;  // place queen

            if (solveNQ(col + 1)) return 1; // solve next column

            board[i][col] = 0; // backtrack
        }
    }
    return 0; // no solution found
}

// Print the solution board
void printBoard() {
	int i,j;
    for ( i = 0; i < N; i++) {
        for ( j = 0; j < N; j++)
            printf("%d ", board[i][j]);
        printf("\n");
    }
}

int main() {
    if (solveNQ(0) == 0) {
        printf("No solution exists\n");
    } else {
        printBoard();
    }
    return 0;
}
