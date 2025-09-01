#include <stdio.h>
#define SIZE 10

int queue1[SIZE], queue2[SIZE];
int front1 = -1, rear1 = -1;
int front2 = -1, rear2 = -1;

// Queue operations
int isEmpty1() { return front1 == -1; }
int isEmpty2() { return front2 == -1; }

void enqueue1(int x) {
    if (rear1 == SIZE - 1) { printf("Queue1 Full!\n"); return; }
    if (front1 == -1) front1 = 0;
    queue1[++rear1] = x;
}
int dequeue1() {
    if (isEmpty1()) return -1;
    int val = queue1[front1];
    if (front1 == rear1) front1 = rear1 = -1;
    else front1++;
    return val;
}

void enqueue2(int x) {
    if (rear2 == SIZE - 1) { printf("Queue2 Full!\n"); return; }
    if (front2 == -1) front2 = 0;
    queue2[++rear2] = x;
}
int dequeue2() {
    if (isEmpty2()) return -1;
    int val = queue2[front2];
    if (front2 == rear2) front2 = rear2 = -1;
    else front2++;
    return val;
}

// Push (costly)
void push(int x) {
    enqueue2(x);

    // Move all elements from queue1 to queue2
    while (!isEmpty1()) {
        enqueue2(dequeue1());
    }

    // Swap queue1 and queue2
    int tempQ[SIZE]; int tempF, tempR;
    // swap data structures by swapping pointers
    int *q1 = queue1, *q2 = queue2;
    for (int i = 0; i < SIZE; i++) {
        tempQ[i] = queue1[i];
        queue1[i] = queue2[i];
        queue2[i] = tempQ[i];
    }
    tempF = front1; front1 = front2; front2 = tempF;
    tempR = rear1;  rear1 = rear2;  rear2 = tempR;

    printf("Pushed %d\n", x);
}

// Pop (simple)
void pop() {
    if (isEmpty1()) {
        printf("Stack Empty!\n");
    } else {
        printf("Popped %d\n", dequeue1());
    }
}

// Display stack
void display() {
    if (isEmpty1()) {
        printf("Stack Empty!\n");
        return;
    }
    printf("Stack elements: ");
    for (int i = front1; i <= rear1; i++) {
        printf("%d ", queue1[i]);
    }
    printf("\n");
}

int main() {
    push(10);
    push(20);
    push(30);

    display();

    pop();
    display();

    push(40);
    push(50);

    display();

    return 0;
}
