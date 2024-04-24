#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define MAX_MSG_SIZE 1024

int main() {
int sockfd;
struct sockaddr_in addr;
char buffer[MAX_MSG_SIZE];

// Create UDP socket
if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
perror("Socket creation failed");
exit(EXIT_FAILURE);
}

int reuse = 1;
if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (void *) &reuse, sizeof (reuse)) < 0)
	perror ("SO_REUSEADDR");

// Set up address to listen on
memset(&addr, 0, sizeof(addr));
addr.sin_family = AF_INET;
addr.sin_addr.s_addr = htonl(INADDR_ANY);
addr.sin_port = htons(PORT);

// Bind socket to address
if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
perror("Bind failed");
exit(EXIT_FAILURE);
}

printf("Receiver listening on port %d...\n", PORT);

while (1) {
// Receive message
if (recv(sockfd, buffer, MAX_MSG_SIZE, 0) == -1) {
perror("Receive failed");
exit(EXIT_FAILURE);
}

// Display received message
printf("Received: %s\n", buffer);
}

close(sockfd);

return 0;
}
