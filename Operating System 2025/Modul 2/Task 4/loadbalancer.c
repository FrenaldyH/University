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
    // Buat message queue
    key_t key = ftok("loadbalancer.c", 65);
    int msgqid = msgget(key, IPC_CREAT | 0666);
    int tot_worker = 3;

    // Terima pesan dari client
    msg_buffer client_msg;
    msgrcv(msgqid, &client_msg, sizeof(client_msg), 1, 0);

    // Catat pesan yang diterima
    FILE *log = fopen("sistem.log", "a");
    fprintf(log, "Recieved at lb: %s #message %d\n", client_msg.content, client_msg.count);
    fclose(log);

    // Distribusi round-robin
    int cur_worker = 1;
    for (int i = 0; i < client_msg.count; i++) {
        client_msg.mtype = cur_worker;
        msgsnd(msgqid, &client_msg, sizeof(client_msg), 0);
        cur_worker = (cur_worker % tot_worker) + 1;
    }

    // Kirim sinyal terminasi
    msg_buffer term_msg;
    strcpy(term_msg.content, "TERMINATE");
    for (int i = 1; i <= tot_worker; i++) {
        term_msg.mtype = i;
        msgsnd(msgqid, &term_msg, sizeof(term_msg), 0);
    }

    // Tunggu worker selesai
    sleep(1);
    msgctl(msgqid, IPC_RMID, NULL);

    // Catat penyelesaian
    log = fopen("sistem.log", "a");
    fprintf(log, "LoadBalancer: selesai mendistribusikan %d pesan\n", client_msg.count);
    fclose(log);

    return 0;
}