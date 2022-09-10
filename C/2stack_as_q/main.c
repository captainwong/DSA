#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Stack {
    int* s;
    int n, top;
}Stack;

typedef struct Queue {
    Stack s1, s2;
}Q;

Stack createStack(int n)
{
    Stack s;
    s.s = malloc((s.n = n) * sizeof(int));
    s.top = -1;
    return s;
}

int stackFull(Stack s) {
    return s.top == s.n - 1;
}

int stackEmpty(Stack s) {
    return s.top == -1;
}

void push(Stack* s, int n) {
    s->s[++s->top] = n;
}

int pop(Stack* s) {
    return s->s[s->top--];
}

void A(Q* q, int n)
{
    if (stackFull(q->s1) && stackEmpty(q->s2)) {
        while (!stackFull(q->s2) && !stackEmpty(q->s1)) {
            push(&q->s2, pop(&q->s1));
        }
    }
    if (stackFull(q->s1)) {
        puts("ERROR:Full");
        return;
    }
    push(&q->s1, n);
}

void D(Q* q)
{
    if (stackEmpty(q->s2)) {
        while (!stackFull(q->s2) && !stackEmpty(q->s1)) {
            push(&q->s2, pop(&q->s1));
        }
    }
    if (stackEmpty(q->s2)) {
        puts("ERROR:Empty");
        return;
    }
    printf("%d\n", pop(&q->s2));
}

int main()
{
    int n1, n2;
    scanf("%d %d", &n1, &n2);
    if (n1 > n2) {
        int t = n1;
        n1 = n2;
        n2 = t;
    }
    Q q;
    q.s1 = createStack(n1);
    q.s2 = createStack(n2);

    char op;
    int n;

    while ((op = getchar()) != EOF) {
        if (op == 'T') break;
        switch (op) {
        case 'A': scanf("%d", &n); A(&q, n); break;
        case 'D': D(&q);
        }
    }

}