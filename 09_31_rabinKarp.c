#include <stdio.h>
#include <string.h>

#define d 256 // number of characters in the input alphabet

void rabinKarp(char text[], char pattern[], int q) {
    int M = strlen(pattern);
    int N = strlen(text);
    int i, j;
    int p = 0; // hash value for pattern
    int t = 0; // hash value for text
    int h = 1;

    // The value of h = pow(d, M-1) % q
    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;

    // Calculate initial hash value for pattern and first window of text
    for (i = 0; i < M; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    // Slide the pattern over text
    for (i = 0; i <= N - M; i++) {
        // Check the hash values
        if (p == t) {
            // Check characters one by one
            for (j = 0; j < M; j++) {
                if (text[i + j] != pattern[j])
                    break;
            }
            if (j == M)
                printf("Pattern found at index %d\n", i);
        }

        // Calculate hash for next window
        if (i < N - M) {
            t = (d * (t - text[i] * h) + text[i + M]) % q;

            if (t < 0)
                t = (t + q);
        }
    }
}

int main() {
    char text[100], pattern[50];
    int q = 101; // A prime number

    printf("Enter the text: ");
    gets(text);

    printf("Enter the pattern: ");
    gets(pattern);

    rabinKarp(text, pattern, q);

    return 0;
}
