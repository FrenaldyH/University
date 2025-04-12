#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node *next;
} node;

typedef struct {
    node *head, *tail;
} queue;

void initQ(queue* q) {
    q->head = NULL;
    q->tail = NULL;
}

int x, y, z, ans1, ans2, i, j;
void push(queue* q, int val) {
    node* newnode = (node*)malloc(sizeof(node));
    newnode->next = NULL;
    newnode->val = val;

    if(q->head == NULL) {
        q->head = q->tail = newnode;
    }
    else {
        q->tail->next = newnode;
        q->tail       = newnode;
    }
}

void solve(queue* q) {
    node* cur = q->head;
    while(cur != NULL) {
        if(y > cur->val)
            ans1++, y -= cur->val;
        if(y >= z)
            ans2++;
        cur = cur->next;
    }
}

int main() {
    queue q;
    initQ(&q);
    ans1 = ans2 = 0;
    scanf("%d%d%d", &x, &y, &z);
    for(j = 0; j < x; j++) {
        scanf("%d", &i);
        push(&q, i);
    }
    solve(&q);

   //  printf("%d %d\n", ans1, ans2);
    printf("%d ", ans2 - (ans2 == x));

    if(ans1 == x) printf("Yes Dapat burger gratis!!!\n");
    else printf("NOO tidak Dapat :(\n");
}

