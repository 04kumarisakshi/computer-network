#include <stdio.h>
#include "buffer.h"
#include<string.h>
#include<stdlib.h>
#include<sys/ipc.h>

unsigned long long toBinary(int n)
{
	unsigned long long bin=0;
	int rem,i=1;
	while(n>0)
	{
		rem=n%2;
		n=n/2;
		bin=bin+rem*i;
		i=i*10;
	}
	return bin;
}

void main()
{
	int msg_id=msgget(1234,0666|IPC_CREAT);

	int num;
	printf("Enter a number :");
	scanf("%d",&num);

	char binary[64],octal[64],hexa[64];

	long int bin=toBinary(num);
	sprintf(binary,"%ld",bin);
	sprintf(octal,"%o",num);
	sprintf(hexa,"%X",num);
	
	msg buffer1,buffer2,buffer3;

	buffer1.type=1;
	buffer2.type=2;
	buffer3.type=3;

	strcpy(buffer1.data,binary);
	strcpy(buffer2.data,octal);
	strcpy(buffer3.data,hexa);

	msgsnd(msg_id,&buffer1,sizeof(buffer1.data),0);
	printf("\nBinary data sent to message queue");

	msgsnd(msg_id,&buffer2,sizeof(buffer2.data),0);
        printf("\nOctal data sent to message queue");

  

	msgsnd(msg_id,&buffer3,sizeof(buffer3.data),0);
        printf("\nHexadecimal data sent to message queue\n");
        
        
        msgctl(msg_id,IPC_RMID,NULL);
}
	
	

