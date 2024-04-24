#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_BUFFER_SIZE 1024

void performBitStuffing(char* input, char* stuffedOutput) {
    int count = 0;
    int index = 0;

    for (int i = 0; i < strlen(input); i++) {
        stuffedOutput[index++] = input[i];

        if (input[i] == '1') {
            count++;
        } else {
            count = 0;
        }

        if (count == 5) {
            stuffedOutput[index++] = '0';
            count = 0;
        }
    }

    stuffedOutput[index] = '\0';
}

int main() {

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Error creating server socket");
        exit(EXIT_FAILURE);
    }


    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8081);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error binding server socket");
        exit(EXIT_FAILURE);
    }

  
    if (listen(serverSocket, 5) == -1) {
        perror("Error listening for connections");
        exit(EXIT_FAILURE);
    }

    printf("Server waiting for incoming connections...\n");


    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);

    if (clientSocket == -1) {
        perror("Error accepting connection");
        exit(EXIT_FAILURE);
    }

    //printf("Connection accepted from %s:%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));


    char bitStream[MAX_BUFFER_SIZE];
    recv(clientSocket, bitStream, sizeof(bitStream), 0);
    bitStream[strlen(bitStream)] = '\0';


    char stuffedStream[MAX_BUFFER_SIZE * 2]; 
    performBitStuffing(bitStream, stuffedStream);


    send(clientSocket, stuffedStream, strlen(stuffedStream), 0);

    printf("Bit-stuffed stream sent back to the client\n");


    close(clientSocket);
    close(serverSocket);

    return 0;
}
