#include <stdio.h>
#define SIZE 10

int stack1[SIZE], stack2[SIZE];
int top1 = -1, top2 = -1;

// Stack operations
void push1(int x) { stack1[++top1] = x; }
int pop1() { return stack1[top1--]; }
void push2(int x) { stack2[++top2] = x; }
int pop2() { return stack2[top2--]; }
int isEmpty1() { return top1 == -1; }
int isEmpty2() { return top2 == -1; }

// Enqueue (push costly)
void enqueue(int x) {
    // Move all from stack1 to stack2
    while (!isEmpty1()) {
        push2(pop1());
    }

    // Push new element to stack1
    push1(x);

    // Move everything back to stack1
    while (!isEmpty2()) {
        push1(pop2());
    }

    printf("Enqueued %d\n", x);
}

// Dequeue (just pop from stack1)
void dequeue() {
    if (isEmpty1()) {
        printf("Queue is Empty!\n");
    } else {
        printf("Dequeued %d\n", pop1());
    }
}

// Display
void display() {
    if (isEmpty1()) {
        printf("Queue is Empty!\n");
    } else {
        printf("Queue elements: ");
        for (int i = top1; i >= 0; i--) {
            printf("%d ", stack1[i]);
        }
        printf("\n");
    }
}

int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);

    display();

    dequeue();
    display();

    enqueue(40);
    enqueue(50);
    display();

    return 0;
}
