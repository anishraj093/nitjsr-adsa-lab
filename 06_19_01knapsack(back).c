#include <stdio.h>

// global variables
int maxProfit = 0;  

// Backtracking function
void knapSackBT(int W, int wt[], int val[], int n, int i, int currWeight, int currProfit) {
    if (i == n) {  // all items considered
        if (currProfit > maxProfit)
            maxProfit = currProfit;
        return;
    }

    // Case 1: include the item if it fits
    if (currWeight + wt[i] <= W) {
        knapSackBT(W, wt, val, n, i+1, currWeight + wt[i], currProfit + val[i]);
    }

    // Case 2: exclude the item
    knapSackBT(W, wt, val, n, i+1, currWeight, currProfit);
}

int main() {
    int val[] = {60, 100, 120};  // values
    int wt[]  = {10, 20, 30};    // weights
    int W = 50;                  // capacity
    int n = sizeof(val) / sizeof(val[0]);

    knapSackBT(W, wt, val, n, 0, 0, 0);
    printf("Maximum value in Knapsack = %d\n", maxProfit);

    return 0;
}
