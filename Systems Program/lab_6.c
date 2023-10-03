#include<stdio.h> 
#include<string.h> 
#include<stdbool.h> 
#define SIZE 4 //number of pages 
#define QUEUE_SIZE 3// max. size of the queue

int front = -1; //points to the front
int rear = -1;  //points to the back
int pageFrames[SIZE]; 
int pageFaults = 0; 

bool isEmpty(){ 
	return rear == -1; 
}

bool isFull(){ 
	return rear == QUEUE_SIZE - 1; 
}

void enqueue(int item){ 
	rear++;
	pageFrames[rear] = item; 
	printf("\n%d inserted into the queue", item);
}

int dequeue(){ 
	if (isFull()){   
		front++;
		if (front > rear)
			front = rear = -1;
		printf("\n%d removed from the queue", pageFrames[front]);
	}	
}

bool isPageHit(int pageNumber){ 
	for (int i = 0; i < SIZE; i++){ 
		if (pageFrames[i] == pageNumber){ 
			return 1; 
		}
	}
	return 0;
}

void managePageFrames(int pageNumber){ 
	dequeue();
	enqueue(pageNumber);
}

int main(){ 
	int pages[SIZE] = {1,2,3,4}; //Case 1
	//int pages[SIZE] = {1,1,2,3}; //Case 2 
	//int pages[SIZE] = {1,2,2,3}; //Case 3  
	//int pages[SIZE] = {1,1,1,1}; //Case 4

	memset(pageFrames, -1, sizeof(pageFrames)); 
	for (int i = 0; i<SIZE; i++){ 
		if(!isPageHit(pages[i])){ 
			pageFaults++; 
			managePageFrames(pages[i]);
		}
	}
	printf("\nTotal number of page faults: %d\n", pageFaults);
	return 0;

}