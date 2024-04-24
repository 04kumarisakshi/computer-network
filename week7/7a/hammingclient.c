#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/udp.h>
#include<arpa/inet.h>


#define SIZE 1024
#define PORT 4440


int main(){

int sockfd=socket(AF_INET,SOCK_DGRAM,0);
struct sockaddr_in addr;

addr.sin_family=AF_INET;
addr.sin_addr.s_addr=inet_addr("127.0.0.1");
addr.sin_port=htons(PORT);
socklen_t addrlen=sizeof(addr);
char buffer[SIZE];
printf("Enter 4bit-data: ");
scanf("%s",buffer);


sendto(sockfd,buffer,SIZE,0,(struct sockaddr*)&addr,sizeof(addr));
char hamCod[SIZE];
recvfrom(sockfd,hamCod,SIZE,0,(struct sockaddr*)&addr,&addrlen);
printf("Calculate Hamming code: %s\n",hamCod);
return 0;
}

