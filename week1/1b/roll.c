#include <stdio.h>
#include <stdlib.h>
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

int compare_roll_numbers(const void *a, const void *b) {
    return ((struct student *)a)->roll_number - ((struct student *)b)->roll_number;
}

int main() {
    key_t key;
    int msgid;
    struct msg_buffer msg;
    struct student students[MAX_STUDENTS];
    int count = 0;

    // Generate a unique key
    key = ftok("Sender.c", 'a');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Get the message queue
    msgid = msgget(key, 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Receive data from message queue
    while (msgrcv(msgid, &msg, sizeof(struct student), 2, IPC_NOWAIT) != -1) {
        students[count++] = msg.data;
    }
    //putting the data back on message queue so that sender process can also read it.(rem-msg_queue pe data delete hota hai.)

    for (int i = 0; i < count; i++) {

        msg.msg_type = 2; 
        msg.data = students[i];
        if (msgsnd(msgid, &msg, sizeof(struct student), 0) == -1) {
            perror("msgsnd");
            exit(EXIT_FAILURE);
        }
    }
    printf("Data recieved and undergoing roll sorting\n");
    // Sort by roll number
    qsort(students, count, sizeof(struct student), compare_roll_numbers);

   printf("Sorted According to Roll Numbers:\n");
    for (int i = 0; i < count; i++) {
        printf("Roll:%d\n", students[i].roll_number);
    }
    

    // Send sorted students back to sender process
    for (int i = 0; i < count; i++) {

        msg.msg_type = 7; 
        msg.data = students[i];
        if (msgsnd(msgid, &msg, sizeof(struct student), 0) == -1) {
            perror("msgsnd");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
