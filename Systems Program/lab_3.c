#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> 
#include <stdint.h>

void *thread_function(void *args){ 
	printf("I am child thread with ID: %lu \n", pthread_self());  

	int *end = args;
	uintptr_t size = (uintptr_t)end;
	int *numbers = malloc(size* sizeof(int));
	for(int i = 0; i< *end; i++){	
		printf("Inserted %d into the array using child thread... \n", i);
	}
	return numbers;
}


int main(int args, char* argv[]){ 
	printf("I am the main thread with ID: %lu \n", pthread_self()); 

	pthread_t tid; 
	int thread_status;
	int end = atoi(argv[1]);
	char *p;

	pthread_create(&tid, NULL, &thread_function, &end); 

	int *numbers;
	pthread_join(tid, (void **)&numbers);

	printf("\n");
	printf("Displaying elements of the array in the parent thread...\n"); 

	
	for (int i = 0; i < end; i++){ 
		printf("Element at index %d: %d \n", i,i);
	}
	free(numbers);

	if (thread_status == 0){
		printf("Thread is still running\n"); 
	}
	else{ 
		printf("Thread has terminated\n");
	}

	return 0;
}