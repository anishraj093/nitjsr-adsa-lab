#include <stdio.h>

#define MAX 100

// stack arrays
int stackL[MAX], stackR[MAX], stackState[MAX];
int top = -1;

// push operation
void push(int l, int r, int state) {
    top++;
    stackL[top] = l;
    stackR[top] = r;
    stackState[top] = state;
}

// merge function
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int L[50], R[50];

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// iterative merge sort using stack
void mergeSort(int arr[], int n) {
    int l, r, state, m;

    // push the full range with state=0 (to split first)
    push(0, n - 1, 0);

    while (top != -1) {
        l = stackL[top];
        r = stackR[top];
        state = stackState[top];
        top--;  // pop

        if (l >= r) continue;

        m = (l + r) / 2;

        if (state == 0) {
            // push current range again with state=1 (to merge later)
            push(l, r, 1);
            // push right and left halves to be sorted
            push(m + 1, r, 0);
            push(l, m, 0);
        } else {
            // merge step
            merge(arr, l, m, r);
        }
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    printArray(arr, n);

    mergeSort(arr, n);

    printf("Sorted array: ");
    printArray(arr, n);

    return 0;
}
