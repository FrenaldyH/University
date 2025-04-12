#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>

#define el printf("\n")
#define ll long long
#define dd double
#define Cls system("cls")

void delay(int ms) {
    clock_t start = clock();
    while(clock() < start + ms);
}

typedef struct Node {
    int job_num, priority;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} PriorityQueue;

void initPQ(PriorityQueue* pq) {
    pq->head = NULL;
}

bool is_emptyPQ(PriorityQueue* pq) {
    return pq->head == NULL;
}

Node* add_node(int job_num, int priority) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->job_num = job_num;
    temp->priority = priority;
    temp->next = NULL;
    return temp;
}

void add_jobPQ(PriorityQueue* pq, int job_num, int priority) { Cls;
    Node* new_node = add_node(job_num, priority);
    if (is_emptyPQ(pq) || priority >= pq->head->priority) {
        new_node->next = pq->head;
        pq->head = new_node;
    } 
    else {
        Node* curr = pq->head;
        while (curr->next && curr->next->priority >= priority)
            curr = curr->next;

        new_node->next = curr->next;
        curr->next = new_node;
    }
    printf("Job %d added with priority %d\n", job_num, priority);
    delay(1000);
}

void popPQ(PriorityQueue* pq) { Cls;
    if (is_emptyPQ(pq)) {
        printf("Queue is empty!\n");
        delay(1000);
        return;
    }
    Node* temp = pq->head;
    printf("Removed Job %d with priority %d\n", temp->job_num, temp->priority);
    pq->head = pq->head->next;
    free(temp);
    delay(1000);
}

void remove_by_jobnum(PriorityQueue* pq, int job_num) { Cls;
    if (is_emptyPQ(pq)) {
        printf("Queue is empty!\n");
        delay(1000);
        return;
    }

    Node *curr = pq->head, *prev = NULL;
    while (curr && curr->job_num != job_num) {
        prev = curr;
        curr = curr->next;
    }

    if (!curr) {
        printf("Job %d not found in queue.\n", job_num);
    } else {
        if (!prev) pq->head = curr->next;
        else prev->next = curr->next;
        printf("Removed Job %d with priority %d\n", curr->job_num, curr->priority);
        free(curr);
    }
    delay(1000);
}

void display(PriorityQueue* pq) { Cls;
    if (is_emptyPQ(pq)) {
        printf("Queue is empty!\n");
        delay(1000);
        return;
    }

    printf("Priority Queue:\n");
    Node* curr = pq->head;
    while (curr) {
        printf("Job %d | Priority: %d\n", curr->job_num, curr->priority);
        curr = curr->next;
    }
    delay(1000);
}

void menu(PriorityQueue* pq) {
    int choice, job, prio;
    do {
        Cls;
        printf("===> Priority Queue\n");
        printf("1. Add job\n");
        printf("2. Remove highest priority job\n");
        printf("3. Remove job by job number\n");
        printf("4. Display job\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice), Cls;

        switch(choice) {
            case 1:
                printf("Enter job number: ");
                scanf("%d", &job);
                printf("Enter priority: ");
                scanf("%d", &prio);
                add_jobPQ(pq, job, prio);
                break;
            case 2:
                popPQ(pq);
                break;
            case 3:
                printf("Enter job number to remove: ");
                scanf("%d", &job);
                remove_by_jobnum(pq, job);
                break;
            case 4:
                display(pq);
                break;
            case 5:
                printf("Exiting...\n");
                delay(1000), Cls;
                break;
            default:
                printf("Invalid choice!\n");
                delay(1000);
        }
    } while (choice != 5);
}

int main() {
    PriorityQueue pq;
    initPQ(&pq);
    menu(&pq);
    Cls;
    return 0;
}
