#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include <arpa/inet.h>
#include<string.h>

int main(int argc, char *argv[])
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

    char *TxBuffer = argv[1];
    char buffer[1024] = {0};
    
    int sent = send(clientSocket, TxBuffer, sizeof(TxBuffer), 0);
    printf("Login info sent to the Server\n");
    printf("Waiting for response\n");

    recv(clientSocket, buffer, 1024, 0); 
    printf("Received from the server --> Login %s\n", buffer);

    

    close(clientSocket);

    return 0;
}