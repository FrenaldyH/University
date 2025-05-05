#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ry, rx, i;
void step(char c) {
    switch (c) {
    case 'U':
        ry++;
        break;
    case 'D':
        ry--;
        break;
    case 'L':
        rx--;
        break;
    case 'R':
        rx++;
        break;
    }
}

typedef struct node {
    int y, x;
    struct node *next;
} node;

typedef struct stack {
    node *top;
    unsigned size;
} stack;

void push(stack *st, int newx, int newy) 
{
    node *newnode = (node*)malloc(sizeof(node));
    st->size++;
    newnode->y = newy;
    newnode->x = newx;
    if (!st->size) newnode->next = NULL;
    else newnode->next = st->top;
    st->top = newnode;
}

void init(stack *st) {
    st->top = NULL;
    st->size = 0;   
    push(st, 0, 0);
}

void pop(stack *st) 
{
    if (st->size > 1) {
        node *temp = st->top;
        st->top = st->top->next;
        free(temp);
        st->size--;
    }
}

int main() {
    char ss[1000];
    scanf("%s", ss);
    stack st;
    init(&st);

    ry = rx = 0;
    for(i = 0; i < strlen(ss); i++) {
        if(ss[i] == 'B') {
            pop(&st);
            rx = st.top->x;
            ry = st.top->y;
        }
        else {
            step(ss[i]);
            push(&st, rx, ry);
        }
    }
    printf("Posisi akhir robot: (%d %d)\n", st.top->x, st.top->y);
}