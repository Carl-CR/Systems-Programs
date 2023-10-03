#include<stdio.h>
#include<stdlib.h> 

#define NO_OF_PROCESSES 5

struct process{
	int pid;
	int burst_time; 
	int priority; 
}; 


int compare(const void * a, const void * b){
	struct process p1 = *(const struct process*)a;
	struct process p2 = *(const struct process*)b;

	if (p1.priority < p2.priority) return -1;
	if (p1.priority > p2.priority) return 1;
	return 0;
}


int main(){ 

	struct process proc[NO_OF_PROCESSES] = { 
		{1, 10, 3}, 
		{2, 1, 1}, 
		{3, 2, 4}, 
		{4, 1, 5},
		{5, 5, 2} 
	};

	int wait_time = 0, turn_around_time = 0; 
	float avg_wait_time = 0;
	
	printf("Before sorting...\n");

	printf("\nProcess\t\t Burst Time\t Priority\n");

	for (int i=0; i<NO_OF_PROCESSES; i++){
		printf("%d \t\t %d \t\t %d\n",proc[i].pid, proc[i].burst_time,proc[i].priority);
	}

	printf("\nAfter sorting...\n");

	printf("\nProcess\t\t Burst Time\t Priority\t Wait Time\t Turn Around Time\n");

	qsort(proc, NO_OF_PROCESSES, sizeof(struct process), compare);

	for(int i = 0; i < NO_OF_PROCESSES; i++){ 
		turn_around_time = proc[i].burst_time + wait_time;
		printf("%d \t\t %d \t\t %d \t\t %d \t\t %d\n",proc[i].pid, proc[i].burst_time, proc[i].priority, wait_time, turn_around_time);
		avg_wait_time = avg_wait_time + wait_time; 
		wait_time = wait_time + proc[i].burst_time;
	}

	printf("Average Wait Time: %.2f\n", avg_wait_time/NO_OF_PROCESSES);

	return 0;

}