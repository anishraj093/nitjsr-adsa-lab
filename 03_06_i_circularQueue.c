#include <stdio.h>
#define size 100 //size of circular queue

int queue[size];
int front=-1,rear=-1;

void enqueue(int value){
	if((front==0&&rear==size-1)||rear+1==front){
		printf("queue is full \n");
	}else{
		if(front==-1)front=0;//first element
		rear=(rear+1)%size;
		queue[rear]=value;
	}
}

void dequeue(){
	if(front==-1)printf("queue is empty \n");
	else{
		if(front==rear){//only one element
			front=rear=-1;
		}else front=(front+1)%size;
	}
}

// Display operation
void display() {
    if (front == -1) {
        printf("Queue is Empty!\n");
    } else {
        printf("Queue elements: ");
        int i = front;
        while (1) {
            printf("%d ", queue[i]);
            if (i == rear)
                break;
            i = (i + 1) % size;
        }
        printf("\n");
    }
}


int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);
    enqueue(50); 

    display();

    dequeue();
    dequeue();

    display();

    enqueue(60);
    enqueue(70);

    display();

    return 0;
}
