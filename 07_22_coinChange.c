#include <stdio.h>

void coinChange(int coins[], int n, int amount) {
    printf("Coins used:\n");
    int i;
    for ( i = 0; i < n; i++) {
        while (amount >= coins[i]) {
            amount -= coins[i];
            printf("%d ", coins[i]);
        }
    }
    printf("\n");
}

int main() {
    // coin denominations (sorted in descending order)
    int coins[] = {10, 5, 1};  
    int n = sizeof(coins) / sizeof(coins[0]);

    int amount = 28;  // example
    printf("Amount: %d\n", amount);

    coinChange(coins, n, amount);

    return 0;
}
