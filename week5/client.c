#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_BUFFER_SIZE 1024

int main() {

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Error creating client socket");
        exit(EXIT_FAILURE);
    }


    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8081);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error connecting to server");
        exit(EXIT_FAILURE);
    }

    printf("Connected to the server\n");


    char bitStream[MAX_BUFFER_SIZE];
    printf("Enter bit-stream: ");
    fgets(bitStream, sizeof(bitStream), stdin);


    send(clientSocket, bitStream, strlen(bitStream), 0);


    char stuffedStream[MAX_BUFFER_SIZE * 2]; 
    recv(clientSocket, stuffedStream, sizeof(stuffedStream), 0);
    stuffedStream[strlen(stuffedStream)] = '\0';


    printf("Received bit-stuffed stream from the server: %s\n", stuffedStream);


    close(clientSocket);

    return 0;
}
