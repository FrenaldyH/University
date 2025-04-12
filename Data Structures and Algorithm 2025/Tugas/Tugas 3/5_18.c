#include <stdio.h>
#include <stdlib.h>
#define S 1000

// Fren -> Not, Equal, AND, OR
// ASCII 0 = 48, A = 65, a = 97

typedef struct nd {
    int v;
    struct nd *nxt;
} nd;

typedef struct {
    nd *t;
    int sz;
} Stk;

void init(Stk *s) {
    s->t = NULL;
    s->sz = 0;
}

nd* crt(int v) {
    nd* n = (nd*)malloc(sizeof(nd));
    n->v = v;
    n->nxt = NULL;
    return n;
}

void push(Stk *s, int v) {
    nd* n = crt(v);
    n->nxt = s->t;
    s->t = n;
    s->sz++;
}

int pop(Stk *s) {
    nd* tmp = s->t;
    int v = tmp->v;
    s->t = tmp->nxt;
    free(tmp);
    s->sz--;
    return v;
}

int top(Stk *s) {
    return s->t->v;
}

int is_empty(Stk *s) {
    return s->t == NULL;
}

void sort(Stk *s1) {
    Stk s2;
    init(&s2);

    while (!is_empty(s1)) {
        int tmp = pop(s1);

        while (!is_empty(&s2) && top(&s2) > tmp) {
            push(s1, pop(&s2));
        }

        push(&s2, tmp);
    }

    // Pindahkan semua elemen dari s2 kembali ke s1
    while (!is_empty(&s2)) {
        push(s1, pop(&s2));
    }
}

void prt(Stk *s) {
    nd* cur = s->t;
    while (cur != NULL) {
        printf("%d ", cur->v);
        cur = cur->nxt;
    }
    printf("\n");
}

int main() {
    Stk s1;
    init(&s1);

    // Input
    int n, x;
    printf("Masukan ukuran data: "); scanf("%d", &n);
    while(n--) {
        scanf("%d", &x);
        push(&s1, x);
    }

    sort(&s1);
    printf("Hasil sort: ");
    prt(&s1);

    return 0;
}