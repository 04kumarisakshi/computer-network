#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_CLIENTS 5
#define BUFFER_SIZE 16

void handle_client(int client_socket) {
char buffer[BUFFER_SIZE];
recv(client_socket, buffer, sizeof(buffer), 0);

struct in_addr ipv4_addr;
int result = inet_pton(AF_INET, buffer, &ipv4_addr);

if (result > 0) {
send(client_socket, "YES", 3, 0);
} else {
send(client_socket, "NO ", 2, 0);
}
printf("\nReceived IPv4 Address: %s",buffer);
printf("\nIPv4 Address verified and result sent back to Client.");

close(client_socket);
}

int main() {
int server_socket, client_socket, addr_size;
struct sockaddr_in server_addr, client_addr;

server_socket = socket(AF_INET, SOCK_STREAM, 0);

server_addr.sin_family = AF_INET;
server_addr.sin_addr.s_addr = INADDR_ANY;
server_addr.sin_port = htons(8080);

bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

listen(server_socket, MAX_CLIENTS);

printf("Server listening on port 8080...\n");

while (1) {
addr_size = sizeof(client_addr);
client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_size);

if (fork() == 0) {
close(server_socket);
handle_client(client_socket);
exit(0);
} else {
close(client_socket);
}
}

return 0;
}
