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

int compare_names(const void *a, const void *b) {
    return strcmp(((struct student *)a)->name, ((struct student *)b)->name);
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
    while (msgrcv(msgid, &msg, sizeof(struct student), 1, IPC_NOWAIT) != -1) {
        students[count++] = msg.data;
    }
    printf("Data recieved and undergoing name sorting\n");
    // Sort by name
    qsort(students, count, sizeof(struct student), compare_names);
    printf("Sorted According to Names:\n");
    for (int i = 0; i < count; i++) {
        printf("Name: %s\n", students[i].name);
    }


    // Send sorted names back to sender process
    for (int i = 0; i < count; i++) {
        msg.msg_type = 2; // Setting message type to 2 to distinguish sorted names
        msg.data = students[i];
        if (msgsnd(msgid, &msg, sizeof(struct student), 0) == -1) {
            perror("msgsnd");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
