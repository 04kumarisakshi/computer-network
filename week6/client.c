#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080
#define BUFFER_SIZE 16

int main() {
int client_socket;
struct sockaddr_in server_addr;
char ipv4_address[BUFFER_SIZE];

client_socket = socket(AF_INET, SOCK_DGRAM, 0);

server_addr.sin_family = AF_INET;
server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
server_addr.sin_port = htons(SERVER_PORT);

connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

printf("Enter IPv4 address (a.b.c.d): ");
scanf("%s", ipv4_address);

send(client_socket, ipv4_address, strlen(ipv4_address), 0)

char response[3];

recv(client_socket, response, sizeof(response), 0);
if(response[0]=='Y')printf("Server response: YES\n");
else printf("Server response: NO\n");

close(client_socket);

return 0;
}
