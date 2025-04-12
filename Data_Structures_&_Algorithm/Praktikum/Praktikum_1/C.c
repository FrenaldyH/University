#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node {
    int val;
    struct node *le, *ri;
} node;

typedef struct list {
    node *head, *tail;
    int size;
} list;

void initL(list* li) {
    li->head = li->tail = NULL;
    li->size = 0;
}

void pushL(list *li, int value)
{
    node *newnode = (node*) malloc(sizeof(node));
    if (newnode) {
        newnode->val = value;
        newnode->ri = newnode->le = NULL;
        
        if (li->size == 0) {
            li->head = li->tail = newnode;
        }
        else {
            newnode->le = li->tail;
            li->tail->ri = newnode;
            li->tail = newnode;
        }
        li->size++;
    }
}

int n, i, x;
void solve(list* li) {
    node* cur = li->head;
    for(int i = 0; i < n; i++) {
        if((i & 1)) {
            printf("%d %d ", cur->val, cur->le->val);
        }
        if(cur->ri != NULL)
            cur = cur->ri;
    }

    if(n % 2 != 0) printf("%d", cur->val);
    printf("\n");
}

int main() {
    list li;
    initL(&li);
    scanf("%d", &n);
    for(i = 0; i < n; i++) {
        scanf(" %d", &x);
        pushL(&li, x);
    }
    solve(&li);
}

