#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include <arpa/inet.h>
#include<string.h>
#include<stdlib.h>

int main()
{
	int clientSocket;

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (clientSocket < 0)
	{
		printf("Error initializing client socket\n");
	}
	else
	{
		printf("Client socket initialized!\n");
	}

	struct sockaddr_in svrAddress;
	svrAddress.sin_family = AF_INET;
	svrAddress.sin_port = htons(27000);
	svrAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

	int connectResult = connect(clientSocket, (struct sockaddr *)& svrAddress, sizeof(svrAddress));
	if (connectResult < 0)
	{
		printf("Error establishing connection\n");
	}
	else
	{
		printf("Connection established\n");
	}
	
	char YesNo[1];

    do {
    	char name[128]; 
		char nameOutput[4096];
		char choice[1];
		char response[4096];
		
    	printf("Please enter your name: ");
		scanf("%s", name); 

		send(clientSocket, name, sizeof(name), 0); 
		//printf("Name sent to the server\n");

		recv(clientSocket, nameOutput, sizeof(nameOutput), 0);
		printf("%s\n", nameOutput);

		printf("Please enter your choice:");
		scanf("%s", choice);
	
		//Sending choice and printing out input
		send(clientSocket, choice, sizeof(choice), 0); 
		recv(clientSocket, response, sizeof(response), 0);
		printf("%s\n", response); 


        printf("Do you need any more information? (Yes = y, No = n):");
        scanf("%s", YesNo);        
    } while (strcmp(YesNo, "y") == 0);

	close(clientSocket);


	return 0;
}