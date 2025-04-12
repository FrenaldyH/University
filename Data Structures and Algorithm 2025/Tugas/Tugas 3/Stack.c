#include <stdlib.h>
#include <stdio.h>

typedef struct stk_t {
    int *el, *top;
    unsigned sz, cap;
} Stk;

void init(Stk *s, unsigned cap) {
    s->el = (int*) malloc(sizeof(int) * cap);
    s->sz = 0;
    s->top = s->el - 1;
    s->cap = cap;
}

_Bool is_empty(Stk *s) {
    return (s->top < s->el);
}

void push(Stk *s, int val) {
    if (s->sz + 1 <= s->cap) {
        *(++s->top) = val;
        s->sz++;
    }
}

void pop(Stk *s) {
    if (!is_empty(s)) {
        s->top--;
        s->sz--;
    }
}

int top(Stk *s) {
    if (!is_empty(s)) {
        return *s->top;
    }
    return 0;
}

int find(Stk *s, int val) {
    for (int i = 0; i < s->sz; i++) {
        if (s->el[i] == val) {
            return i;
        }
    }
    return -1;
}

void edit(Stk *s, int idx, int new_val) {
    if (idx >= 0 && idx < s->sz) {
        s->el[idx] = new_val;
    }
}

void print(Stk *s) {
    Stk tmp;
    init(&tmp, s->cap);

    while (!is_empty(s)) {
        printf("%d ", top(s));
        push(&tmp, top(s));
        pop(s);
    }
    
    while(!is_empty(&tmp)) {
        push(s, top(&tmp));
        pop(&tmp);
    }
}

int main(int argc, char const *argv[]) {
    Stk s;
    int cap, ch, val, idx, new_val;
    
    puts("Enter the capacity of the stack :");
    scanf("%d", &cap);
    
    init(&s, cap);
    
    while(1) {
        printf("\nStack Operations Menu:\n");
        puts("1. Push an element");
        puts("2. Pop an element");
        puts("3. Print stack");
        puts("4. Search for an element");
        puts("5. Edit an element");
        puts("6. Exit");
        scanf("%d", &ch);

        switch(ch) {
            case 1:
                if(s.sz >= cap) {
                    puts("Maximum stack capacity reached.");
                } else {
                    puts("Enter value to push: ");
                    scanf("%d", &val);
                    push(&s, val);
                    printf("%d", s.sz);
                    puts("Element pushed to stack.");
                }
                break;
            
            case 2:
                if (!is_empty(&s)) {
                    pop(&s);
                    puts("Element popped from stack.");
                } else {
                    puts("Stack is empty.");
                }
                break;
            
            case 3:
                puts("Current stack: ");
                print(&s);
                printf("\n");
                break;
            
            case 4:
                puts("Enter value to search: ");
                scanf("%d", &val);
                idx = find(&s, val);
                if (idx != -1) {
                    printf("Element %d found at index %d.\n", val, idx);
                } else {
                    printf("Element not found in the stack.\n");
                }
                break;
            
            case 5:
                printf("Enter index to edit: ");
                scanf("%d", &idx);
                if(idx >= cap) {
                    puts("invalid index.");
                } else {
                    printf("Enter new value: ");
                    scanf("%d", &new_val);
                    edit(&s, idx, new_val);
                    printf("Element at index %d edited to %d.\n", idx, new_val);
                }
                break;
            
            case 6:
                puts("Exiting program.");
                free(s.el);
                return 0;

            default:
                puts("Invalid choice. Please try again.");
        }
    }
    return 0;
}