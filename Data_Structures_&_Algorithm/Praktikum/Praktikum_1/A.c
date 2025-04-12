#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node {
    int val;
    struct node *next;
} node;

typedef struct stack {
    node *top;
    unsigned size;
} stack;

void initS(stack* s) {
    s->top = NULL;
}

bool is_emptyS(stack *s) {
    return (s->top == NULL);
}

bool vokal(int a) {
    char c = a;
    if(c == 'A' || c == 'I' || c == 'U' || c == 'E' || c == 'O')
        return true;
    if(c == 'a' || c == 'i' || c == 'u' || c == 'e' || c == 'o')
        return true;
    return false;
}

void stack_push(stack *s, int value) 
{
    node *newnode = (node*) malloc(sizeof(node));
    if (newnode) {
        s->size++;
        newnode->val = value;
        
        if (is_emptyS(s)) newnode->next = NULL;
        else newnode->next = s->top;

        s->top = newnode;
    }
}

void solve(stack* in) {
    stack ot;
    node* cur = in->top;
    while(cur != NULL) {
        printf("%c", (char)cur->val);
        if(vokal(cur->val)) 
            printf("%c", (char)cur->val);
        cur = cur->next;
    }
    printf("\n");
}

int main() {
    stack in;
    initS(&in);
    char cc[110];
    scanf(" %s", cc);
    for(int i = 0; i < strlen(cc); i++) {
        stack_push(&in, (int)cc[i]);
    }
    solve(&in);
}