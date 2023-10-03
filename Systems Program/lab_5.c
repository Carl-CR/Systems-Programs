#include <stdio.h>

#define BLOCK_SIZE 5 
#define PROCESS_SIZE 5

struct process{ 
	int pid; 
	int psize; 
};

void bestfit(int* blocks, struct process* proc, int allocations[]){ 
	//printf("Test\n");
	for (int i = 0; i < PROCESS_SIZE; i++){ 
		int bestIdx = -1; 
		for(int j = 0; j < BLOCK_SIZE; j++){ 
			if(blocks[j] >= proc[i].psize){ 
				if (bestIdx == -1)
					bestIdx = j; 
				else if (blocks[bestIdx] > blocks[j])
					bestIdx = j;
			}
		}

		if (bestIdx != -1){ 
			allocations[i] = bestIdx + 1;
			blocks[bestIdx] -= proc[i].psize;
		}
	}
}

int main(){ 
	int blocks[BLOCK_SIZE] = {100, 500, 200, 300, 600};
	int allocations[BLOCK_SIZE] = {-1, -1, -1, -1, -1};

	struct process proc[PROCESS_SIZE] = { 
		{1, 212},
		{2, 417},
		{3, 112},
		{4, 426},
		{5, 80}
	};

	bestfit(blocks, proc, allocations);

	printf("Process ID\t Process Size\t Block\n");
	for (int i=0; i<PROCESS_SIZE; i++){
		printf("%d \t\t %d \t\t %d\n",proc[i].pid, proc[i].psize, allocations[i]);
	}

	return 0; 
		
}