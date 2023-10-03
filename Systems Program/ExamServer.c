#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<sys/socket.h>
#include<netdb.h>
#include<unistd.h>
#include <pthread.h>

struct EmailDetails
{
	char * from;
	char * to;
	char * subject;
	char * body;
};

struct Email
{
	char *userName;
    struct EmailDetails details;
};

void populateData(struct Email *emails)
{
    // Email 1
    emails[0].userName = "JobsS";
    emails[0].details.from = "Bill";
    emails[0].details.to = "Jobs";
    emails[0].details.subject = "Finance Presentation";
    emails[0].details.body = "Looking forward to our meeting on finance";

    // Email 2
    emails[1].userName = "BillG";
    emails[1].details.from = "Warren";
    emails[1].details.to = "Bill";
    emails[1].details.subject = "Dinner";
    emails[1].details.body = "It was lovely meeting you over dinner meeting";

    // Email 3
    emails[2].userName = "WarrenB";
    emails[2].details.from = "Elon";
    emails[2].details.to = "Warren";
    emails[2].details.subject = "SpaceX";
    emails[2].details.body = "How's new SpaceX project going?";

    // Email 4
    emails[3].userName = "JobsS";
    emails[3].details.from = "Elon";
    emails[3].details.to = "Jobs";
    emails[3].details.subject = "Twitter";
    emails[3].details.body = "How is it going at Twitter?";
}

char* searchEmails(struct Email *emails, char *username)
{
    // Mandatory Method to fill in
    // searches for emails for a user name and returns in the form a char *
}
void *manage_clients(void *arg)
{
	int clientSocket = *(int *)arg; 

	char RxBuffer[1024];
	char list[258] = {"test"}; 

	int received = recv(clientSocket, RxBuffer, sizeof(RxBuffer), 0); 

	if (received == 0){ 
		printf("Client Disconnected\n"); 

	}
	else{ 
		send(clientSocket, list, strlen(list), 0);
	}

}


int main() {

    int serverSocket;
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == 0)
	{
		printf("Error creating server socket\n");
	}
	else
	{
		printf("Server Socket created\n");
	}

	struct sockaddr_in svrAddress;
	svrAddress.sin_family = AF_INET;
	svrAddress.sin_addr.s_addr = INADDR_ANY; 
	svrAddress.sin_port =  htons(27000); 

	int lenAddress = sizeof(svrAddress);

	int bindResult = bind(serverSocket, (struct sockaddr *)&svrAddress, lenAddress);

	if (bindResult < 0)
	{
		printf("Error binding socket\n");
	}
	else
	{
		printf("Socket bound successfully\n");
	}

	int listenResult = listen(serverSocket, 1);
	if (listenResult < 0)
	{
		printf("Error listening to server socket\n");
	}
	else
	{
		printf("Listening to the socket\n");
	}

	int clientSocket;
	while (1)
	{
		// Fill in to manage multiple client connections
		
	}

	close(serverSocket);

    return 0;
}