#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define MAX_MSG_SIZE 1024
#define BROADCAST_ADDR "255.255.255.255"

int main() {
int sockfd;
struct sockaddr_in addr;
char buffer[MAX_MSG_SIZE];

// Create UDP socket
if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
perror("Socket creation failed");
exit(EXIT_FAILURE);
}

// Enable broadcast
int broadcast_enable = 1;
if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast_enable, sizeof(broadcast_enable)) == -1) {
perror("setsockopt(SO_BROADCAST) failed");
exit(EXIT_FAILURE);
}

// Set up broadcast address
memset(&addr, 0, sizeof(addr));
addr.sin_family = AF_INET;
addr.sin_port = htons(PORT);
addr.sin_addr.s_addr = inet_addr(BROADCAST_ADDR);

while (1) {
printf("Enter message to broadcast (type 'QUIT' to exit): ");
fgets(buffer, MAX_MSG_SIZE, stdin);

// Remove newline character
buffer[strcspn(buffer, "\n")] = '\0';

// Check if user wants to quit
if (strcmp(buffer, "QUIT") == 0) {
break;
}

// Broadcast message
if (sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
perror("Broadcast failed");
exit(EXIT_FAILURE);
}
}

close(sockfd);

return 0;
}
