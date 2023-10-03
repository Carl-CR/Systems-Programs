#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> 
#include <stdint.h>

void *thread_function(void *num){
	int answer = *((int *)num);
	int try = 1; 
	int guess = -1; 
	while (guess != answer) { 
		guess =rand()%10 + 1;
		printf("Child thread --> : |Try %d: | I am guessing %d \n", try, guess); 
		try += 1;
		if (guess == answer)
			printf("Child thread --> I have finally guessed it. The number was %d! \n",answer);
	}

}


int main(int args, char* argv[]){ 
	srand(time(NULL));
	int num = rand()%10 + 1;
	printf("I am the Parent Thread and I have a chosen secret number: %d \n", num);
	
	pthread_t tid;

	pthread_create(&tid, NULL, &thread_function, &num); 
	pthread_join(tid, NULL); 
}