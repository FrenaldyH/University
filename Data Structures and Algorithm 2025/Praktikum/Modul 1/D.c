#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node {
    int val;
    struct node *next;
} node;

typedef struct {
    node *top;
    int size;
} pqueue;

void initpq(pqueue* pq) {
    pq->top = NULL;
}

int trans(char c) {
    if(c == ')') return 0;
    if(c == '!') return 1;
    if(c == '@') return 2;
    if(c == '#') return 3;
    if(c == '$') return 4;
    if(c == '%') return 5;
    if(c == '^') return 6;
    if(c == '&') return 7;
    if(c == '*') return 8;
    if(c == '(') return 9;
    return -1;
}

int n, m, i, y;
void solve(pqueue* pq, int val) {
    node* newnode = (node*)malloc(sizeof(node));
    newnode->val = val;
    newnode->next = NULL;

    if(val <= m && pq->top == NULL) {
        pq->top = newnode;
    }
    else if(val <= m) 
    {
        if(pq->top->val < val) {
            newnode->next = pq->top;
            pq->top = newnode;
        }
        else {
            node *temp = pq->top;
            while(temp->next != NULL && temp->next->val > val)
                temp = temp->next;
            if(temp->next == NULL) {
                temp->next = newnode;
            }
            else {
                newnode->next = temp->next;
                temp->next = newnode;
            }
        }
    }

    if(pq->top != NULL && pq->top->val == m) {
        while(pq->top != NULL && pq->top->val == m) {
            printf("%d ", pq->top->val);
            node* cur = pq->top;
            if(pq->top->next != NULL)
                pq->top = cur->next, free(cur);
            else {pq->top = NULL;}
            m--;
        }
    }
    printf("\n");
}

void debug(pqueue* pq) {
    node* cur = pq->top;
    while(cur != NULL) {
        printf("%d ", cur->val);
        cur = cur->next;
    }
    printf("\n");
}

int main() {
    char x[6];
    scanf("%d %d", &n, &m);
    pqueue pq;
    initpq(&pq);
    while(n--) {
        scanf(" %s", x), y = 0;
        for(i = 0; i < strlen(x); i++) {
            y = y * 10;
            y += trans(x[i]);
        }
        solve(&pq, y);
    }
    // debug(&pq);
}