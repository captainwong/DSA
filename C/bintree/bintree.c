// https://pintia.cn/problem-sets/15/problems/732

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char ElementType;
typedef struct TNode* Position;
typedef Position BinTree;
struct TNode {
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

BinTree CreatBinTree(); /* 实现细节忽略 */
BinTree createBinTree(const char* s)
{
    if (strlen(s) == 0 || *s == '0') return NULL;
    BinTree root = malloc(sizeof(*root));
    root->Data = *s++;
    root->Left = root->Right = NULL;
    BinTree Level[128] = { NULL };
    int N = 0;
    Level[N++] = root;

    while (*s) {
        BinTree level[128] = { NULL };
        int n = 0;
        for (int i = 0; i < N; i++) {
            BinTree t = Level[i];
            if (t) {
                BinTree l = NULL, r = NULL;
                if (*s) {
                    if (*s != '0') {
                        l = malloc(sizeof(*l));
                        l->Left = l->Right = NULL;
                        l->Data = *s;
                        t->Left = l;
                    }
                    s++;
                }
                if (*s) {
                    if (*s != '0') {
                        r = malloc(sizeof(*r));
                        r->Left = r->Right = NULL;
                        r->Data = *s;
                        t->Right = r;
                    }
                    s++;
                }
                level[n++] = l;
                level[n++] = r;
            }
        }
        memcpy(Level, level, sizeof(Level));
        N = n;
    }
    return root;
}

void InorderTraversal(BinTree BT)
{
    if (!BT) return;
    InorderTraversal(BT->Left);
    printf(" %c", BT->Data);
    InorderTraversal(BT->Right);
}

void PreorderTraversal(BinTree BT)
{
    if (!BT) return;
    printf(" %c", BT->Data);
    PreorderTraversal(BT->Left);
    PreorderTraversal(BT->Right);
}

void PostorderTraversal(BinTree BT)
{
    if (!BT) return;
    PostorderTraversal(BT->Left);
    PostorderTraversal(BT->Right);
    printf(" %c", BT->Data);
}

typedef struct Node {
    BinTree t;
    struct Node* next;
}Node;

typedef struct Q {
    Node* head;
    Node* tail;
}Q;

void enq(Q* q, BinTree t) {
    Node* p = malloc(sizeof(*p));
    p->t = t;
    p->next = NULL;
    if (q->head == NULL) {
        q->head = q->tail = p;
    } else {
        q->tail->next = p;
        q->tail = p;
    }
}

BinTree deq(Q* q) {
    BinTree p = q->head->t;
    q->head = q->head->next;
    if (!q->head) { q->tail = NULL; }
    return p;
}

void LevelorderTraversal(BinTree BT)
{
    if (!BT) return;
    Q q = { 0 };
    enq(&q, BT);
    while (q.head != NULL) {
        BinTree t = deq(&q);
        printf(" %c", t->Data);
        if (t->Left) enq(&q, t->Left);
        if (t->Right) enq(&q, t->Right);
    }
}

int main()
{
    BinTree BT = createBinTree("ABCDFGI00E00H");
    printf("Inorder:");    InorderTraversal(BT);    printf("\n");
    printf("Preorder:");   PreorderTraversal(BT);   printf("\n");
    printf("Postorder:");  PostorderTraversal(BT);  printf("\n");
    printf("Levelorder:"); LevelorderTraversal(BT); printf("\n");
    return 0;
}
/* 你的代码将被嵌在这里 */
