#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int time = 1, ch;
typedef struct node {
    int id, priority_code, timestamp;
    char nama[37];
    struct node *next;
} node;

typedef struct {
    node *top;
    int size;
} list;

void initls(list *ls) {
    ls->top = NULL;
    ls->size = 0;
}

void push(list *ls, node val) {
    node *newnode = (node*)malloc(sizeof(node));
    strcpy(newnode->nama, val.nama);
    newnode->priority_code = val.priority_code;
    newnode->timestamp = time++;
    newnode->id = val.id;
    newnode->next = NULL;
    
    if(!ls->size) {
        ls->top = newnode;
        ls->top->next = NULL;
        ls->size++;
        return;
    }

    if(newnode->priority_code > ls->top->priority_code) {
        newnode->next = ls->top;
        ls->top = newnode;
    }
    else {
        node *temp = ls->top;
        while(temp->next != NULL && temp->next->priority_code >= newnode->priority_code 
                && temp->timestamp < newnode->timestamp) {
                    temp = temp->next;
                }
        if(temp->next == NULL) {
            temp->next = newnode;
            newnode = NULL;
        }
        else {
            newnode->next = temp->next;
            temp->next = newnode;
        }
    }
    ls->size++;
    return; 
}

void display(list *ls) {
    if(!ls->size) {
        printf("Antrean kosong . . .\n");
        return;
    }

    int i = 1;
    node* temp = ls->top;
    for(; temp != NULL; i++, temp = temp->next) {
        printf("--> Laporan %d <--\n", i);
        printf("ID laporan: %d\n", temp->id);
        printf("Nama laporan: %s\n", temp->nama);
        printf("Kode prioritas: %d\n", temp->priority_code);
        printf("Timestamp kedatangan: %d\n", temp->timestamp);
    }
    return;
}

void process(list *ls) {
    if(!ls->size) {
        printf("Tidak ada laporan yang dapat di proses . . .\n");
        return;
    }
    node *temp = ls->top;
    ls->top = temp->next;
    printf("--> Proses laporan\n");
    printf("ID laporan: %d\n", temp->id);
    printf("Nama laporan: %s\n", temp->nama);
    printf("Kode prioritas: %d\n", temp->priority_code);
    printf("Timestamp kedatangan: %d\n", temp->timestamp);
    free(temp), ls->size--;
}

int main() {
    list ls;
    initls(&ls);
    do {
        printf("Menu:\n");
        printf("1) Tambahkan Laporan baru\n");
        printf("2) Proses laporan (hapus dari list dan tampilkan datanya)\n");
        printf("3) Tampilkan semua laporan dalam antrean\n");
        printf("4) Keluar dari program\n");
        printf("Input: "), scanf("%d", &ch);

        switch (ch) {
        case 1:
            node temp;
            printf("--> Masukan laporan:\n");
            printf("ID laporan: "), scanf("%d", &temp.id);
            getchar();
            printf("Nama laporan: "), scanf("%s", temp.nama);
            printf("Kode prioritas: "), scanf("%d", &temp.priority_code);
            printf("\n");
            push(&ls, temp);
            break;
        case 2:
            process(&ls);
            printf("\n");
            break;
        case 3:
            display(&ls);
            printf("\n");
            break;
        case 4:
            printf("Keluar program . . .\n");
            break;
        default:
            printf("Pilihan menu tidak valid  . . .\n");
            break;
        }
    } while(ch != 4);
}