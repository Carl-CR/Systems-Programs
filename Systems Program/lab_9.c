//Server code
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>

int main()
{
    int serverSocket;

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket == 0)
    {
        printf("Error creating server socket\n");
        return -1;
    }
    else
    {
        printf("Server socket created!\n");
    }

    struct sockaddr_in svrAddress;
    svrAddress.sin_family = AF_INET;
    svrAddress.sin_addr.s_addr = INADDR_ANY;
    svrAddress.sin_port = htons(27000);

    int lenAddress = sizeof(svrAddress);

    int bindResult = bind(serverSocket, (struct sockaddr *)&svrAddress, lenAddress);
    if (bindResult < 0)
    {
        printf("Error binding to the socket\n");
        return -1;
    }
    else
    {
        printf("Socket bound successfully\n");
    }

    int listenResult = listen(serverSocket, 1);
    if (listenResult < 0)
    {
        printf("Error listening to the socket\n");
        return -1;
    }
    else
    {
        printf("Listening to socket\n");
    }

    int clientSocket = accept(serverSocket, (struct sockaddr *)&svrAddress, (socklen_t *)&lenAddress);
    if (clientSocket < 0)
    {
        printf("Error accepting connections\n");
        return -1;
    }
    else
    {
        printf("Accepting new connections!\n");
    }

    printf("Connection Established\n");

    //Recieve this value
    float fahrenheit;
    //Create this value and then send it to client
    float celsius;

    int received = recv(clientSocket, &fahrenheit, sizeof(fahrenheit), 0);
    if (received > 0)
    {
        celsius = (fahrenheit - 32) * 5 / 9;
        printf("Received from Client %.2f\n", fahrenheit);
        send(clientSocket, &celsius, sizeof(celsius), 0);
    }

    close(clientSocket);
    close(serverSocket);

    return 0;
}



/*
//Client code
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    int clientSocket;
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (clientSocket < 0) {
        printf("Error initializing client socket\n");
        return -1;
    } else {
        printf("Client socket initialized!\n");
    }

    struct sockaddr_in svrAddress;
    svrAddress.sin_family = AF_INET;
    svrAddress.sin_port = htons(27000);
    svrAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    int connectResult = connect(clientSocket, (struct sockaddr *)&svrAddress, sizeof(svrAddress));
    if (connectResult < 0) {
        printf("Error establishing connection\n");
        return -1;
    } else {
        printf("Connection established\n");
    }

    float fahrenheit = atof(argv[1]);
    float celsius;

    send(clientSocket, &fahrenheit, sizeof(fahrenheit), 0);
    printf("Temperature %.2f sent to server for conversion into Celsius\n", fahrenheit);

    int received = recv(clientSocket, &celsius, sizeof(celsius), 0);

    if (received > 0) {
        printf("Received from Server after conversion %.2f\n", celsius);
    }

    close(clientSocket);

    return 0;
}
*/