#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>
#define MAXDATA 1000
int main(){
	int cs=socket(AF_UNIX, SOCK_STREAM, 0);
	struct sockaddr_un saddr;
	saddr.sun_family= AF_UNIX;
	strcpy(saddr.sun_path,"./mysocket");
	connect(cs,(struct sockaddr *)&saddr, sizeof(saddr));
    char data[MAXDATA], ds[MAXDATA];
	while(1){
	    printf("Enter the bit stream you want to check: \n");
	    scanf("%s",data);
	    write(cs,(void *)data,strlen(data)+1);
	    read(cs,(void *)ds, MAXDATA);
	    printf("Changed bit stream is: %s.\n",ds);
	}
    close(cs);
	return 0;
}
