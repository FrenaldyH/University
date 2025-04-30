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

int main() {
    // Baca input user
    char input[256];
    printf("Masukkan pesan dan jumlah (format: <pesan>;<count>): ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    // Parsing input
    char *message = strtok(input, ";");
    char *count_str = strtok(NULL, ";");
    int count = atoi(count_str);

    // Buat message queue
    key_t key = ftok("loadbalancer.c", 65);
    int msgqid = msgget(key, IPC_CREAT | 0666);

    // Kirim pesan ke load balancer
    msg_buffer msg;
    msg.mtype = 1;  // Tipe 1 untuk client->loadbalancer
    strcpy(msg.content, message);
    msg.count = count;
    msgsnd(msgqid, &msg, sizeof(msg), 0);

    // Catat log
    FILE *log = fopen("sistem.log", "a");
    fprintf(log, "Message from client: %s\nMessage count: %d\n", msg.content, msg.count);
    fclose(log);

    return 0;
}