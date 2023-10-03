#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include <arpa/inet.h>

int main()
{
	int clientSocket;

	clientSocket = socket(AF_INET, SOCK_DGRAM, 0);

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

	char name[128]; 
	char response[128];

	printf("Please enter the username");
	scanf("%s", name);

	send(clientSocket, name, sizeof(name), 0); 
	recv(clientSocket, response, sizeof(response), 0);
	printf("%s\n", response);

	
	close(clientSocket);

	return 0;
}