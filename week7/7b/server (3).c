#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>

#define SIP "127.0.0.1"
#define SPORT "8080"
#define CIP "127.0.0.1"
#define CPORT "8081"

//#define MAX 1024

pthread_t r,w;


void *rec(void* args){
	char data[100];
	int server_fd, server_len, client_len;
	server_fd=socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in saddr, caddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port=htons(8080);
	caddr.sin_family = AF_INET;
	caddr.sin_port=htons(8081);
	inet_aton(CIP,&(caddr.sin_addr));
	inet_aton(SIP,&(saddr.sin_addr));
	
	bind(server_fd, (struct sockaddr *)&saddr, sizeof(saddr));
	while(1){
		printf("\nWaiting from client.\n");
		client_len=sizeof(caddr);
		recvfrom(server_fd, (void*)data, sizeof(data), 0, (struct sockaddr*)&caddr, &client_len);
		printf("\nData received from client: ");
		printf("%s", data);
		if (strcasecmp(data,"quit")==0) break;
		
	}
	close(server_fd);
}

void *sen(void* args){
	char data[100];
	int server_fd, server_len, client_len;
	server_fd=socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in saddr, caddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port=htons(8080);
	caddr.sin_family = AF_INET;
	caddr.sin_port=htons(8081);
	inet_aton(CIP,&(caddr.sin_addr));
	
	server_len = sizeof(saddr);
	bind(server_fd, (struct sockaddr *)&saddr, server_len);
	while(1){
		printf("\nEnter message: ");
		fgets(data,sizeof(data),stdin);
		data[strlen(data)-1]='\0';
		
		sendto(server_fd, (void*)data, strlen(data)+1, 0, (struct sockaddr *)&caddr, sizeof(caddr));
		if (strcasecmp(data,"quit")==0) break;
			
	}
	close(server_fd);
}

int main() {
	
	pthread_create(&r,NULL,(void*)&rec,NULL);
	pthread_create(&w,NULL,(void*)&sen,NULL);
	
	pthread_join(r,NULL);
	pthread_join(w, NULL);
		
	return 0;
}

