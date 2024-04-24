#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 50

struct student {
    char name[MAX_NAME_LENGTH];
    int roll_number;
};

struct msg_buffer {
    long msg_type;
    struct student data;
};

int main() {
    key_t key;
    int msgid;
    struct msg_buffer msg;

    key = ftok("Sender.c", 'a');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
    int n;
    printf("How many student details you want to enter?\n");
    scanf("%d",&n);
    printf("Enter details for %d students:\n",n);
    for (int i = 0; i < n; i++) {
        printf("student %d:\n", i + 1);
        printf("Name: ");
        scanf("%s", msg.data.name);
        printf("Roll Number: ");
        scanf("%d", &msg.data.roll_number);

        msg.msg_type = 1;
        if (msgsnd(msgid, &msg, sizeof(struct student), 0) == -1) {
            perror("msgsnd");
            exit(EXIT_FAILURE);
        }
        printf("Data for student %d sent to message queue\n", i + 1);
    }

    sleep(10);
    
    printf("\nData  Sorted according to name Received from Sorting process:\n");
    while (msgrcv(msgid, &msg, sizeof(struct student), 2, IPC_NOWAIT) != -1) {
        printf("Name: %s  Roll Number: %d\n", msg.data.name, msg.data.roll_number);
    }
    sleep(5);
    printf("Data Sorted according to the roll recieved form the sorting Process\n");
    while(msgrcv(msgid,&msg, sizeof(struct student), 7, IPC_NOWAIT)!=-1)
    {
        printf("Name: %s, Roll Number: %d\n", msg.data.name, msg.data.roll_number);
    }
    // Delete the message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}
