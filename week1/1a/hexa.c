#include <stdio.h>
#include "buffer.h"
#include<string.h>
#include<stdlib.h>
#include<sys/ipc.h>

void main()
{
        int msg_id=msgget(1234,0666 | IPC_CREAT);

        msg buffer;
        msgrcv(msg_id,&buffer,sizeof(buffer.data),3,0);

        printf("Hexadecimal value is %s \n",buffer.data);
        
        msgctl(msg_id,IPC_RMID,NULL);
}

