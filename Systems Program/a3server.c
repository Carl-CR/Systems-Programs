#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include <arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>
#include <dirent.h>
#include <errno.h>

const int MaxMsg = 50;

time_t Starttime;

FILE *logfile;

//To get the prompt with name included
char* getList(char* testN){ 
	char* list = malloc(512);

//Hardcoded message for the menu
	sprintf(list, R"(
Hello %s

To get information about benefits, please select from the following:
1. Canada Workers Benefits
2. Canada Child Benefits
3. Registered Disability Savings Plan
4. War Veterans Allowance
5. Disability Tax Credit
6. Canada Dental Benefits
	)",testN);

	return list;

}


//To get the benefits
char* getBenefitInfo(int serial)
{
    char buffer[2048];

    //Opening file
    //When reading the file i made each benefits into a single line so 1. is line 1 and so on
    FILE* file = fopen("Benefits_Canada.txt", "r");
    if (file == NULL) {
        printf("Error: could not open file.\n");
        fclose(file); 
        return NULL;
    }

    else
    {
        //printf("File opened successfully!\n");

        while(fgets(buffer, sizeof(buffer), file))
        {
           	//Split the information using ";"
            char* serialNumber = strtok(buffer, ";");
            char* code = strtok(NULL, ";");
            char* name = strtok(NULL, ";");
            char* description = strtok(NULL, ";");
            char* link = strtok(NULL, ";");

            //Will return the desired serial number with all the information
            if (atoi(serialNumber) == serial)
            {
                // Creating a buffer to store the benefit information
                char* benefitInfo = malloc(2048);

//Harcoded message with information formatted
                sprintf(benefitInfo, R"(
Please find below information about %s

%s (%s):
%s

Please find more information at: 
%s)", name, name, code, description, link);

            // Closing the file
            fclose(file);

            // Returning the benefit information
            return benefitInfo;
            }
        }
    }
}



// Method to run on each thread
void *manage_clients(void * args)
{
	// Getting the client socket by casting it back to an integer
	int clientSocket = *(int *)args;

	// A buffer to store the information received from the client
	char RxBuffer[1024];

	//Declare list 
	char list[512];

	int msg = 0;

	//Opeing and writing in the log file
	logfile = fopen("log.txt", "w");


	// Loop to keep receiving information from the client
	while(msg < MaxMsg)
	{
		// receiving data from the client in RxBuffer
		int received = recv(clientSocket, RxBuffer, sizeof(RxBuffer), 0);

		// This means no bytes received and hence client is expected to have disconnected.
		if (received == 0)
		{
			printf("Client Disconnected\n");
			break;
		}
		else 
		{
			//temp list to store information 
			char* temp; 

			// Showing data received from the client
			//printf("Received from the Client --> %s\n", RxBuffer);

			//To see if the RxBuffer matches with any of the choices that are being asked if not, 
			//it will assume that a name is being sent and return the welcome message with the menu
			if (RxBuffer[0] == '1'){ 
				//Calling the function and putting the message into temp
				//Then copying the temp into the list that we will return 
				temp = getBenefitInfo(1);
				strcpy(list, temp);
				free(temp);
				printf("Requested Information Sent\n");
				
				//Logging into the file
				time(&Starttime);
    			fputs(ctime(&Starttime), logfile); 
    			fputs("CWB information requested \n",logfile); 
			}
			else if (RxBuffer[0] == '2'){ 
				//Calling the function and putting the message into temp
				//Then copying the temp into the list that we will return
				temp = getBenefitInfo(2);
				strcpy(list, temp);
				free(temp);
				printf("Requested Information Sent\n");

				//Logging into the file
				time(&Starttime);
    			fputs(ctime(&Starttime), logfile); 
    			fputs("CCB information requested \n",logfile);
			}
			else if (RxBuffer[0] == '3'){ 
				//Calling the function and putting the message into temp
				//Then copying the temp into the list that we will return
				temp = getBenefitInfo(3);
				strcpy(list, temp);
				free(temp);
				printf("Requested Information Sent\n");

				//Logging into the file
				time(&Starttime);
    			fputs(ctime(&Starttime), logfile); 
    			fputs("RDSP information requested \n",logfile);
			}
			else if (RxBuffer[0] == '4'){ 
				//Calling the function and putting the message into temp
				//Then copying the temp into the list that we will return
				temp = getBenefitInfo(4);
				strcpy(list, temp);
				free(temp);
				printf("Requested Information Sent\n");

				//Logging into the file
				time(&Starttime);
    			fputs(ctime(&Starttime), logfile); 
    			fputs("WVA information requested \n",logfile);
			}
			else if (RxBuffer[0] == '5'){ 
				//Calling the function and putting the message into temp
				//Then copying the temp into the list that we will return
				temp = getBenefitInfo(5);
				strcpy(list, temp);
				free(temp);
				printf("Requested Information Sent\n");

				//Logging into the file
				time(&Starttime);
    			fputs(ctime(&Starttime), logfile); 
    			fputs("DTC information requested \n",logfile);
			}
			else if (RxBuffer[0] == '6'){ 
				//Calling the function and putting the message into temp
				//Then copying the temp into the list that we will return
				temp = getBenefitInfo(6);
				strcpy(list, temp);
				free(temp);
				printf("Requested Information Sent\n");

				//Logging into the file
				time(&Starttime);
    			fputs(ctime(&Starttime), logfile); 
    			fputs("CDB information requested \n",logfile);
			}

			else{ 
				//Calling the function and putting the message into temp
				//Then copying the temp into the list that we will return
				temp = getList(RxBuffer);
				strcpy(list, temp);
				free(temp);

				//Logging into the file
				time(&Starttime);
    			fputs(ctime(&Starttime), logfile); 
    			fputs("Menu sent \n",logfile);
    			fputs("Welcome Message Sent \n",logfile);
			}

			// Sending back the acknowledgement to the client
			send(clientSocket, list, strlen(list), 0);

			msg++;
		}
	}

	fputs("\n", logfile);
	fclose(logfile);

	//closing client socket
	close(clientSocket);


	// Exiting the thread without passing any information back to the main thread
	pthread_exit(NULL);
}

int main()
{

	int serverSocket;

	// creating server socket with TCP
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (serverSocket == 0)
	{
		printf("Error creating server socket\n");
	}
	else
	{
		//printf("Server socket created!\n");	
	}

	// creating server information to be passed to the bind function
	struct sockaddr_in svrAddress;
	// using IPv4 family
	svrAddress.sin_family = AF_INET;

	// using current loopback address
	svrAddress.sin_addr.s_addr = INADDR_ANY;

	// using port 27000 by converting it into bytes to transfer over the network
	svrAddress.sin_port = htons(27000);

	int lenAddress = sizeof(svrAddress);

	// binding the socket 
	int bindResult = bind(serverSocket, (struct sockaddr *)&svrAddress, lenAddress);
	if (bindResult < 0)
	{
		printf("Error binding to the socket\n");
	}
	else
	{
		//printf("Socket bound successfully\n");
	}

	// listening at the server socket with 1 client in queue
	int listenResult = listen(serverSocket, 1);
	if (listenResult < 0)
	{
		printf("Error listening to the socket\n");
	}
	else
	{
		//printf("Listening to socket\n");
	}

	// creating socket for client
	int clientSocket;
	char RxBuffer[128] = {};
	
	// Infinite loop to make server run indefinitely
	while (1)
	{
		// accepting incoming client connections
		clientSocket= accept(serverSocket, (struct sockaddr *)&svrAddress, (socklen_t *)&lenAddress);
		if (clientSocket < 0)
		{
			printf("Error accepting connections\n");
		}
		else
		{
			//printf("Accepting new connections!\n");
		}
	
		printf("Listening to incoming connection\n");

		pthread_t tid;

		// creating a thread by passing it a method and a parameter to work on
		if (pthread_create(&tid, NULL, manage_clients, (void *)&clientSocket) != 0)
		{
			printf("Error creating thread\n");
		}
		
	}

	// closing server socket
	close(serverSocket);

	return 0;
}