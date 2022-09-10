#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline()
{
    int C = 16, n = 0, c;
    char* s = malloc(C);
    while ((c = getchar()) != EOF) {
        if (c == '\n')break;
        s[n++] = c;
        if (n == C - 1) {
            C <<= 2;
            char* t = malloc(C);
            memcpy(t, s, n);
            free(s);
            s = t;
        }
    }
    s[n] = '\0';
    return s;
}

char* readtill(char e)
{
    int C = 16, n = 0, c;
    char* s = malloc(C);
    while ((c = getchar()) != EOF) {
        if (c == e)break;
        s[n++] = c;
        if (n == C - 1) {
            C <<= 2;
            char* t = malloc(C);
            memcpy(t, s, n);
            free(s);
            s = t;
        }
    }
    s[n] = '\0';
    return s;
}

char* readlinen(int* N)
{
    int C = 16, n = 0, c;
    char* s = malloc(C);
    while ((c = getchar()) != EOF) {
        if (c == '\n')break;
        s[n++] = c;
        if (n == C - 1) {
            C <<= 2;
            char* t = malloc(C);
            memcpy(t, s, n);
            free(s);
            s = t;
        }
    }
    s[n] = '\0';
    *N = n;
    return s;
}

int readline_static(char* s, int len)
{
    int c, n = 0;
    while ((c = getchar()) != EOF && n < len - 1) {
        if (c == '\n')break;
        s[n++] = c;
    }
    s[n] = '\0';
    return n;
}


//typedef struct Node {
//    int val;
//    struct Node* next;
//}Node;
//
//void append(Node** pa, Node** pae, int val)
//{
//    Node* p = malloc(sizeof(Node));
//    p->val = val;
//    p->next = NULL;
//    if (*pae) {
//        (*pae)->next = p;
//        (*pae) = p;
//    } else {
//        *pa = *pae = p;
//    }
//}
//typedef struct Node {
//    int val;
//    struct Node* prev;
//}Node;
//
//void append(Node** pae, int val)
//{
//    Node* p = malloc(sizeof(Node));
//    p->val = val;
//    if (*pae) {
//        p->prev = *pae;
//        (*pae) = p;
//    } else {
//        p->prev = NULL;
//        *pae = p;
//    }
//}
