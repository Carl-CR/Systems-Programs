#include<stdio.h>
#include<unistd.h>
#include<stdlib.h> 
#include<sys/wait.h>


int main(int args, char* argv[])
{ 
	printf("Program name %s\n", argv[0]); 
	char* cmd1 = argv[1]; 
	char* cmd2 = argv[2];

	if (fork()== 0){ 
		char* argument_list[] = {cmd1, NULL};
		printf("I am a child with ID:%d\n", getpid());
		printf("I'll execute:%s\n", cmd1);
		printf("Below are the results for:\n");
		printf("\n"); 
		execvp(cmd1, argument_list);
	}
	else{
		char* argument_list[] = {cmd2, NULL}; 
		wait(NULL);
		printf("\n");
		printf("I am a parent with ID:%d\n", getpid());
		printf("I'll execute:%s\n", cmd2);
		printf("Below are the results for:\n");
		printf("\n"); 
		execvp(cmd2, argument_list);
	}

	return 0; 
}
