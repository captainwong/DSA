/*
https://pintia.cn/problem-sets/15/problems/710

���ݽṹ���㷨��Ŀ�������ģ�
7-2 һԪ����ʽ�ĳ˷���ӷ�����
���� 20
���� DS�γ���
��λ �㽭��ѧ
��ƺ����ֱ�������һԪ����ʽ�ĳ˻���͡�

�����ʽ:
�����2�У�ÿ�зֱ��ȸ�������ʽ������ĸ���������ָ���ݽ���ʽ����һ������ʽ������ϵ����ָ��������ֵ��Ϊ������1000�������������ּ��Կո�ָ���

�����ʽ:
�����2�У��ֱ���ָ���ݽ���ʽ����˻�����ʽ�Լ��Ͷ���ʽ�������ϵ����ָ�������ּ��Կո�ָ�������β�����ж���ո������ʽӦ���0 0��

��������:
4 3 4 -5 2  6 1  -2 0
3 5 20  -7 4  3 1
�������:
15 24 -25 22 30 21 -10 20 -21 8 35 6 -33 5 14 4 -15 3 18 2 -6 1
5 20 -4 4 -5 2 9 1 -2 0
���볤������
16 KB
ʱ������
200 ms
�ڴ�����
64 MB

*/

#define _CRT_SECURE_NO_WARNINGS
#if 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Item {
    int coefficient;
    int exponent;
}Item;

Item imul(Item a, Item b)
{
    Item c;
    c.coefficient = a.coefficient * b.coefficient;
    c.exponent = a.exponent + b.exponent;
    return c;
}

typedef struct Polynomial {
    Item* items;
    int n;
}Polynomial;

int cmpItem(const void* a, const void* b)
{
    Item* A = (Item*)a;
    Item* B = (Item*)b;
    if (A->exponent > B->exponent) {
        return -1;
    } else if (A->exponent < B->exponent) {
        return 1;
    } else {
        return 0;
    }
}

Polynomial sortPolynomial(Polynomial a)
{
    qsort(a.items, a.n, sizeof(Item), cmpItem);
    return a;
}

Polynomial simplify(Polynomial p)
{
    p = sortPolynomial(p);
    Polynomial q = { 0 };
    q.items = malloc(p.n * sizeof(Item));
    int i = 0;
    while (p.items[i].coefficient == 0 && i < p.n) {
        i++;
    }
    if (i == p.n) {
        goto end;
    }

    Item prev = p.items[i];
    for (++i; i < p.n; i++) {
        if (p.items[i].coefficient == 0) { continue; }
        if (prev.exponent == p.items[i].exponent) {
            prev.coefficient += p.items[i].coefficient;
        } else {
            if (prev.coefficient != 0) {
                q.items[q.n++] = prev;
            }
            prev = p.items[i];
        }
    }
    if (prev.coefficient != 0) {
        q.items[q.n++] = prev;
    }

end:
    if (q.n == 0) {
        Item item = { 0 };
        q.items[q.n++] = item;
    }
    if (q.n < p.n) {
        q.items = realloc(q.items, q.n * sizeof(Item));
    }
    return q;
}

Polynomial padd(Polynomial a, Polynomial b)
{
    Polynomial c = { 0 };
    c.items = malloc((a.n + b.n) * sizeof(Item));
    memcpy(c.items, a.items, a.n * sizeof(Item));
    memcpy(c.items + a.n, b.items, b.n * sizeof(Item));
    c.n = a.n + b.n;
    c = simplify(c);
    return c;
}


Polynomial multiply(Polynomial a, Polynomial b)
{
    Polynomial c = { 0 };
    c.items = malloc((a.n * b.n) * sizeof(Item));
    for (int i = 0; i < a.n; i++) {
        for (int j = 0; j < b.n; j++) {
            c.items[c.n++] = imul(a.items[i], b.items[j]);
        }
    }
    c = simplify(c);
    return c;
}

Polynomial readPolynomial()
{
    Polynomial p = { 0 };
    scanf("%d", &p.n);
    p.items = malloc(p.n * sizeof(Item));
    for (int i = 0; i < p.n; i++) {
        scanf("%d %d", &p.items[i].coefficient, &p.items[i].exponent);
    }
    return p;
}

void print(Polynomial p)
{
    for (int i = 0; i < p.n; i++) {
        printf("%s%d %d", i == 0 ? "" : " ",
               p.items[i].coefficient, p.items[i].exponent);
    }
    printf("\n");
}

int main()
{
    Polynomial a = readPolynomial();
    Polynomial b = readPolynomial();

    Polynomial sum = padd(a, b);
    Polynomial product = multiply(a, b);
    print(product);
    print(sum);
}
#endif

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char c;
    struct Node* l, * r;
}Node;

Node* readTree()
{
    int n;
    scanf("%d\n", &n);
    Node** d = malloc(n * sizeof(Node*));
    int check[10] = { 0 };
    for (int i = 0; i < n; i++) {
        d[i] = malloc(sizeof(Node));
        d[i]->c = 0;
        d[i]->l = d[i]->r = NULL;
    }
    for (int i = 0; i < n; i++) {
        char c, l, r;
        scanf("%c %c %c\n", &c, &l, &r);
        d[i]->c = c;
        if (l == '-') {
            d[i]->l = NULL;
        } else {
            d[i]->l = d[l - '0'];
            check[l - '0'] = 1;
        }
        if (r == '-') {
            d[i]->r = NULL;
        } else {
            d[i]->r = d[r - '0'];
            check[r - '0'] = 1;
        }
    }
    Node* root = NULL;
    for (int i = 0; i < n; i++) {
        if (!check[i]) {
            root = d[i];
            break;
        }
    }
    free(d);
    return root;
}

int isIsomorphic(Node* a, Node* b)
{
    if (!a && !b) { return 1; }
    if (!a || !b) return 0;
    if (a->c != b->c) return 0;
    return (isIsomorphic(a->l, b->l) && isIsomorphic(a->r, b->r)) ||
        (isIsomorphic(a->l, b->r) && isIsomorphic(a->r, b->l));

}

int main()
{
    Node* t1 = readTree();
    Node* t2 = readTree();
    printf("%s\n", isIsomorphic(t1, t2) ? "Yes" : "No");
}