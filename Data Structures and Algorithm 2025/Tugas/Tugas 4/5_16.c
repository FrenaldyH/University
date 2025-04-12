#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>

#define Cls system("cls")
#define el printf("\n")
#define ll long long
#define dd double

void delay (int mili_seconds) {
    clock_t st_time  = clock();
    for(; clock() < st_time + mili_seconds;);
}

typedef struct Node {
    int val;
    struct Node* next;
} Node;

typedef struct {
    Node* top;
} Stack;

typedef struct {
    Stack stin, stot;
} Queue;

void initS(Stack* s) {
    s->top = NULL;
}

bool is_emptyS(Stack* s) {
    return s->top == NULL;
}

void pushS(Stack* s, int val) {
    Node* newnode = (Node*)malloc(sizeof(Node));
    newnode->val = val;
    newnode->next = s->top;
    s->top = newnode;
}

void popS(Stack* s) {
    if(is_emptyS(s)) return;
    s->top = s->top->next;
}

int peekS(Stack* s) {
    return s->top->val;
}   

void moveS(Queue* q) {
    if(!is_emptyS(&q->stot)) return;
    while(!is_emptyS(&q->stin)) {
        pushS(&q->stot, peekS(&q->stin));
        popS(&q->stin);
    }
}

void initQ(Queue* q) {
    initS(&q->stin);
    initS(&q->stot);
}

bool is_emptyQ(Queue* q) {
    return is_emptyS(&q->stin) && is_emptyS(&q->stot);
}

void pushQ(Queue* q, int val) {
    pushS(&q->stin, val);
}

void peekQ(Queue* q) {
    if(is_emptyQ(q)) {
        printf("Queue is empty!\n");
        delay(1000);
        return;
    }
    moveS(q);
    printf("Front queue: %d", peekS(&q->stot));
    delay(1000); 
}

void popQ(Queue* q) {
    if(is_emptyQ(q)) {
        printf("Queue is empty!\n");
        delay(1000);
        return;
    }
    moveS(q);
    popS(&q->stot);
    printf("Queue deleted successfully!");
    delay(1000);
}

void menuQ(Queue* q) {
    int chc, val;
    do {
        Cls;
        printf("===> Queue Menu using 2 Stack\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Front\n");
        printf("4. Check Empty\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &chc), Cls;

        switch(chc) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &val);
                pushQ(q, val);
                break;
            case 2:
                popQ(q);
                break;
            case 3:
                peekQ(q); el;
                break;
            case 4:
                printf(is_emptyQ(q) ? "Queue is empty!" : "Queue is not empty!"), el;
                delay(1000);
                break;

            case 5:
                printf("Exiting...\n");
                delay(1000);
                break;

            default:
                printf("Invalid choice, please try again.\n");
                delay(1000);
        }
    } while (chc != 5);
}

int main() {
    Queue q;
    initQ(&q);
    menuQ(&q);
    Cls;
    return 0;
}
