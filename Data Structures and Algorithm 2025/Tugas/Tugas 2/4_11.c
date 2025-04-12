#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define S 1000

// Fren -> Not, Equal, AND, OR
// ASCII 0 = 48, A = 65, a = 97

typedef struct node {
    char v; 
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

node* add_node(char val) {
    node* newnode = (node*)malloc(sizeof(node));
    newnode->l = NULL;
    newnode->r = NULL;
    newnode->v = val; 
    return newnode;
}

void insert_front(LinkedList *list, char val) {
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

void insert_back(LinkedList *list, char val) {
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
        printf("%c", cur->v);
        cur = cur->r;
    }
    printf("\n");
}

void create_list_from_string(LinkedList *list, char* str) {
    int i, len = strlen(str);
    for(i = 0; i < len; i++) {
        insert_back(list, str[i]);
    }
}

void delete_node(LinkedList *list, char val) {
    if(list->head == NULL) return;

    node* cur = list->head;
    while(cur != NULL && cur->v != val) {
        cur = cur->r;
    }
    if(cur != NULL) {
        if(cur->l == NULL) {  
            list->head = cur->r;
            if (list->head) list->head->l = NULL;
        } 
        else if(cur->r == NULL) {  
            list->tail = cur->l;
            list->tail->r = NULL;
        } 
        else {  
            cur->l->r = cur->r;
            cur->r->l = cur->l;
        }

        free(cur);
        list->size--;

        if (list->size == 0) {  
            list->head = NULL;
            list->tail = NULL;
        }
    }
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

bool anagram(LinkedList *list1, LinkedList *list2) {
    if(list1->size != list2->size) return false;

    node *i = list1->head;
    while(i != NULL) {
        node *j = list2->head;
        bool flag = false;
        
        while(j != NULL) {
            if(j->v == i->v) {
                node* next_j = j->r; 
                delete_node(list2, j->v);
                j = next_j; 
                flag = true; 
                break;
            }
            j = j->r;
        }
        if(!flag) return false;
        i = i->r;
    }
    return true;
}


int main() {
    LinkedList list1, list2;
    init_list(&list1);
    init_list(&list2);

    char str1[S + 1], str2[S + 1];
    scanf("%s %s", str1, str2);
    
    create_list_from_string(&list1, str1);
    create_list_from_string(&list2, str2);

    printf("%d\n", anagram(&list1, &list2));
    
    clear_list(&list1);
    clear_list(&list2);
}
