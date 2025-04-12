#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define S 1000

// Fren -> Not, Equal, AND, OR
// ASCII 0 = 48, A = 65, a = 97

typedef struct node {
    int idx;
    struct node *l, *r;
} node;

typedef struct {
    node *head, *tail;
    int size;
} LinkedList;

void init_list(LinkedList *list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

node* add_node(int val) {
    node* newnode = (node*)malloc(sizeof(node));
    newnode->l = NULL;
    newnode->r = NULL;
    newnode->idx = val; 
    return newnode;
}

void insert_front(LinkedList *list, int val) {
    node* newnode = add_node(val);
    if(list->head == NULL) {
        list->head = newnode;
        list->tail = newnode;
    } else {
        newnode->r = list->head;
        list->head->l = newnode;
        list->head = newnode;
    }
    list->size++;
}

void insert_back(LinkedList *list, int val) {
    node* newnode = add_node(val);
    if(list->tail == NULL) {
        list->head = newnode;
        list->tail = newnode;
    } else {
        newnode->l = list->tail;
        list->tail->r = newnode;
        list->tail = newnode;
    }
    list->size++;
}

void print_list(LinkedList *list) {
    node* cur = list->head;
    while(cur != NULL) {
        printf("%d", cur->idx);
        cur = cur->r;
    }
    printf("\n");
}

void solve(LinkedList *list, int m) {
    list->tail->r = list->head;

    node* cur = list->head;
    while(list->size > 1) {
        for(int i = 1; i < m; i++)
            cur = cur->r;
        // printf("%d ", cur->idx);
        cur->l->r = cur->r;
        cur->r->l = cur->l;
        cur = cur->r;
        list->size--;
    }
    printf("%d\n", cur->idx);
}

void clear_list(LinkedList *list) {
    node* cur = list->head;
    while(cur != NULL) {
        node* tp = cur;
        cur = cur->r;
        free(tp);
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

int main() {
    LinkedList list;
    init_list(&list);

    int n, m, i;
    scanf(" %d %d", &n, &m);
    for(i = 1; i <= n; i++) {
        insert_back(&list, i);
    }
    solve(&list, m);
}