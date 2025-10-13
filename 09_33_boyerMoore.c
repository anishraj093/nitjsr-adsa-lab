#include <stdio.h>
#include <string.h>
#define NO_OF_CHARS 256

// Function to create the bad character heuristic table
void badCharHeuristic(char *pattern, int M, int badchar[]) {
    for (int i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;

    for (int i = 0; i < M; i++)
        badchar[(int)pattern[i]] = i;
}

// Boyer-Moore search function
void search(char *text, char *pattern) {
    int M = strlen(pattern);
    int N = strlen(text);

    int badchar[NO_OF_CHARS];
    badCharHeuristic(pattern, M, badchar);

    int s = 0; // shift of the pattern with respect to text
    while (s <= (N - M)) {
        int j = M - 1;

        // Keep reducing j while characters match
        while (j >= 0 && pattern[j] == text[s + j])
            j--;

        // If pattern is found
        if (j < 0) {
            printf("Pattern occurs at index %d\n", s);
            s += (s + M < N) ? M - badchar[(int)text[s + M]] : 1;
        } else {
            int shift = j - badchar[(int)text[s + j]];
            s += (shift > 1) ? shift : 1;
        }
    }
}

// Driver code
int main() {
    char text[100], pattern[50];

    printf("Enter the text: ");
    gets(text);

    printf("Enter the pattern: ");
    gets(pattern);

    search(text, pattern);

    return 0;
}
