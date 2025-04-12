#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define S 1000

// Fren -> Not, Equal, AND, OR
// ASCII 0 = 48, A = 65, a = 97

typedef struct node {
    int v;
    struct node *l, *r;
} node;

node* add_node(int val) {
    node* newnode = (node*)malloc(sizeof(node));
    newnode->l = NULL;
    newnode->r = NULL;
    newnode->v = val; 
    return newnode;
}

void insert_front(node** head, node** tail, int val) {
    node* newnode = add_node(val);
    if(*head == NULL) {
        *head = newnode;
        *tail = newnode;
        return;
    }
    newnode->r = *head;
    (*head)->l = newnode;
    *head = newnode;
}

void insert_back(node** head, node** tail, int val) {
    node* newnode = add_node(val);
    if(*tail == NULL) {
        *head = newnode;
        *tail = newnode;
        return;
    }
    newnode->l = *tail;
    (*tail)->r = newnode;
    *tail = newnode;
}

void print_list(node* head) {
    node* cur = head;
    while(cur != NULL) {
        printf("%d", cur->v);
        cur = cur->r;
    }
    printf("\n");
}

void clear_list(node* head) {
    node* cur = head;
    while(cur != NULL) {
        node* tp = cur;
        cur = cur->r;
        free(tp);
    }
}

void create_list_from_string(node** head, node** tail, char* num) {
    int i, len = strlen(num);
    for(i = 0; i < len; i++) {
        insert_back(head, tail, num[i] - '0');
    }
}

void equalize_length(node** head1, node** tail1, node** head2, node** tail2) {
    node *cur1 = *tail1, *cur2 = *tail2;
    while(cur1->l != NULL || cur2->l != NULL) {
        if(cur1->l == NULL && cur2->l != NULL) {
            insert_front(head1, tail1, 0);
        }
        if(cur1->l != NULL && cur2->l == NULL) {
            insert_front(head2, tail2, 0);
        }
        if(cur1->l != NULL) cur1 = cur1->l;
        if(cur2->l != NULL) cur2 = cur2->l;
    }
}

void add_linked_lists(node** head1, node** tail1, node** head2, node** tail2) {
    node *cur1 = *tail1, *cur2 = *tail2;
    while(cur1 != NULL) {
        cur1->v += cur2->v;
        if(cur1->v > 9) {
            if(cur1->l == NULL) {
                insert_front(head2, tail2, 0);
                insert_front(head1, tail1, cur1->v / 10);
            } else {
                cur1->l->v += (cur1->v / 10);
            }
            cur1->v %= 10;
        }
        cur1 = cur1->l;
        cur2 = cur2->l;
    }
}

int main() {
    node* head1 = NULL;
    node* tail1 = NULL;
    node* head2 = NULL;
    node* tail2 = NULL;

    char num1[S + 1], num2[S + 1];
    scanf("%s %s", num1, num2);
    
    create_list_from_string(&head1, &tail1, num1);
    create_list_from_string(&head2, &tail2, num2);

    equalize_length(&head1, &tail1, &head2, &tail2);
    add_linked_lists(&head1, &tail1, &head2, &tail2);

    print_list(head1);
    clear_list(head1);
}
