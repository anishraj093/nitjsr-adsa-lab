#include <stdio.h>
#include <stdlib.h>

// structure for job
typedef struct {
    int id;
    int deadline;
    int profit;
} Job;

// comparison function for sorting (descending profit)
int compare(const void* a, const void* b) {
    Job* j1 = (Job*)a;
    Job* j2 = (Job*)b;
    return j2->profit - j1->profit;
}

// function to perform job sequencing
void jobSequencing(Job jobs[], int n) {
    // sort jobs by profit
    qsort(jobs, n, sizeof(Job), compare);

    int result[n];   // store job IDs in slots
    int slot[n];     // to keep track of free slots

    // initialize slots as free
    int i,j; 
    for ( i = 0; i < n; i++) slot[i] = 0;

    // assign jobs
    for ( i = 0; i < n; i++) {
        // find free slot before job's deadline
        for ( j = jobs[i].deadline - 1; j >= 0; j--) {
            if (slot[j] == 0) {
                result[j] = i;
                slot[j] = 1;
                break;
            }
        }
    }

    // print the result
    printf("Selected jobs for maximum profit:\n");
    for ( i = 0; i < n; i++) {
        if (slot[i])
            printf("Job %d (Profit %d, Deadline %d)\n",
                   jobs[result[i]].id,
                   jobs[result[i]].profit,
                   jobs[result[i]].deadline);
    }
}

int main() {
    Job jobs[] = {
        {1, 2, 100},
        {2, 1, 19},
        {3, 2, 24},
        {4, 1, 25},
        {5, 3, 15}
    };
    int n = sizeof(jobs) / sizeof(jobs[0]);

    jobSequencing(jobs, n);
    return 0;
}

