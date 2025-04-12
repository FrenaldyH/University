#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
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

int eval(char *exp) {
    Stk s;
    init(&s);

    for (int i = 0; exp[i]; ++i) {
        if (isdigit(exp[i])) {
            push(&s, exp[i] - '0');
        } else {
            int op2 = pop(&s);
            int op1 = pop(&s);

            switch (exp[i]) {
                case '+': push(&s, op1 + op2); break;
                case '-': push(&s, op1 - op2); break;
                case '*': push(&s, op1 * op2); break;
                case '/': push(&s, op1 / op2); break;
                default: 
                    printf("Opr tidak valid: %c\n", exp[i]);
                    exit(1);
            }
        }
    }

    return pop(&s);
}

int main() {
    char exp[] = "23+84/*6-";
    printf("Hasil: %d\n", eval(exp));
    return 0;
}