#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define sz sizeof

typedef struct msg_buffer {
    long mtype;
    char content[256];
    int count;
} msg_buffer;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <worker_id>\n", argv[0]);
        return 1;
    }

    int worker_id = atoi(argv[1]);
    int msg_count = 0;

    // Akses message queue
    key_t key = ftok("loadbalancer.c", 65);
    int msgqid = msgget(key, 0666);

    while (1) {
        msg_buffer msg;
        msgrcv(msgqid, &msg, sizeof(msg), worker_id, 0);

        if (strcmp(msg.content, "TERMINATE") == 0) {
            // Catat total pesan yang diproses
            FILE *log = fopen("sistem.log", "a");
            fprintf(log, "Worker %d: %d message\n", worker_id, msg_count);
            fclose(log);
            break;
        }

        // Catat penerimaan pesan
        FILE *log = fopen("sistem.log", "a");
        fprintf(log, "Worker%d: message received\n", worker_id);
        fclose(log);
        msg_count++;
    }

    return 0;
}