#include <stdio.h>
#include "buffer.h"
#include<string.h>
#include<stdlib.h>
#include<sys/ipc.h>

void main()
{
        int msg_id=msgget(1234,0666 | IPC_CREAT);

    msg buffer2;
       
	msgrcv(msg_id,&buffer2,sizeof(buffer2.data),2,0);

        printf("Octa  value is %s \n",buffer2.data);
        
        msgctl(msg_id,IPC_RMID,NULL);
}

