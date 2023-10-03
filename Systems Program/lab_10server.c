//Server Code
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<pthread.h>
#include<arpa/inet.h>

struct Login
{   
    char userName[8]; 
    char password[8];
};

struct Login logins[5] = {{"john", "12345"}, {"steve", "canada"}, 
                            {"bill", "ontario"}, {"elon", "tesla"}, 
                            {"tim", "apple"} };

//char test[] = "test";
int result;

// Method to run on each thread
void *manage_clients(void * args)
{
    // Getting the client socket by casting it back to an integer
    int clientSocket = *(int *)args;

    // A buffer to store the information received from the client
    char RxBuffer[1024] = {};

    // Loop to keep receiving information from the client
    while(1)
    {
        // receiving data from the client in RxBuffer
        int received = recv(clientSocket, RxBuffer, sizeof(RxBuffer), 0);

        // This means no bytes received and hence client is expected to have disconnected.
        if (received == 0)
        {
            //printf("Client Disconnected\n");
            break;
        }
        else 
        {
            // Showing data received from the client
            //printf("Test: %s\n",test );
            //printf("Received from the Client --> %s\n", RxBuffer);
            printf("Client requesting for authentication...\n");
            printf("Authentication response sent...\n");

            
            //printf("Result %d\n",result);
            for (int i = 0; i < 5; i++){ 
                result = strcmp(RxBuffer, logins[i].userName); 
            }

            if (result == 0){
                send(clientSocket, "successful", 10, 0);
            }
            else if (result != 0){
                send(clientSocket, "unsuccessful", 12, 0);
            }
            
        }
    }
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
        printf("Server socket created!\n"); 
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
        printf("Socket bound successfully\n");
    }

    // listening at the server socket with 1 client in queue
    int listenResult = listen(serverSocket, 1);
    if (listenResult < 0)
    {
        printf("Error listening to the socket\n");
    }
    else
    {
        printf("Listening to socket\n");
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
            printf("Accepting new connections!\n");
        }
    
        printf("Connection Established with %s\n", inet_ntoa(svrAddress.sin_addr));

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