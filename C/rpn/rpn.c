/*
https://pintia.cn/problem-sets/15/problems/827
7-20 ���ʽת��
���� 25
���� DS�γ���
��λ �㽭��ѧ
�������ʽ��ǰ׺��ʾ������׺��ʾ���ͺ�׺��ʾ������ʽ���ճ�ʹ�õ��������ʽ�ǲ�����׺��ʾ��������Ԫ�����λ�������������м䡣����Ƴ�����׺���ʽת��Ϊ��׺���ʽ��

�����ʽ:
������һ���и��������ո����׺���ʽ���ɰ���+��-��*��\�Լ���������()�����ʽ������20���ַ���

�����ʽ:
��һ�������ת����ĺ�׺���ʽ��Ҫ��ͬ������������������ţ�֮���Կո�ָ�������β�����ж���ո�

��������:
2+3*(7-4)+8/4
�������:
2 3 7 4 - * + 8 4 / +
���볤������16 KB
ʱ������400 ms
�ڴ�����64 MB
*/



#include <stdio.h>
#include <ctype.h>

typedef enum Operator {
    Add, Sub, Mul, Div, LP, RP, EOO, OpCount,
}Operator;

Operator char2op(char op)
{
    switch (op) {
    case '+': return Add;
    case '-': return Sub;
    case '*': return Mul;
    case '/': return Div;
    case '(': return LP;
    case ')': return RP;
    default: return EOO;
    }
}

char op2char(Operator op)
{
    char ops[] = "+-*/()\0";
    return ops[op];
}

typedef enum Priority {
    Less, Equal, Greater,
}Priority;

Priority cmp(Operator op1, Operator op2)
{
    static const char table[OpCount][OpCount] = {
        //       +    -    *    /    (    )    0
        /* + */ '>', '>', '<', '<', '<', '>', '>',
        /* - */ '>', '>', '<', '<', '<', '>', '>',
        /* * */ '>', '>', '>', '>', '<', '>', '>',
        /* / */ '>', '>', '>', '>', '<', '>', '>',
        /* ( */ '<', '<', '<', '<', '<', '=', ' ',
        /* ) */ ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        /* 0 */ '<', '<', '<', '<', '<', ' ', '=',
    };
    char op = table[op1][op2];
    if (op == '<') return Less;
    else if (op == '>') return Greater;
    else if (op == '=') return Equal;
    else return -1;
}

void read(char* expr)
{
    int c;
    while ((c = getchar()) != EOF) {
        if (c == '\n')break;
        *expr++ = c;
    }
    *expr = '\0';
}

double calc(double a, double b, Operator op)
{
    switch (op) {
    case Add: return a + b;
    case Sub: return a - b;
    case Mul: return a * b;
    case Div: return a / b;
    }
    return -1;
}

double readn(char** s, char* rpn, int* prlen)
{
    double v = **s - '0';
    rpn[(*prlen)++] = **s;
    while (isdigit(*++*s)) {
        v = v * 10 + **s - '0';
        rpn[(*prlen)++] = **s;
    }
    if (**s != '.') {
        rpn[(*prlen)++] = ' ';
        return v;
    }
    rpn[(*prlen)++] = **s;
    double fraction = 0.1;
    while (isdigit(*++*s)) {
        v += fraction * (**s - '0');
        fraction *= 0.1;
        rpn[(*prlen)++] = **s;
    }
    rpn[(*prlen)++] = ' ';
    return v;
}

int main()
{
    Operator sop[21] = { 0 };
    int optop = -1;
    sop[++optop] = EOO;
    char expr[21];
    read(expr);
    char rpn[1024] = { 0 };
    int rlen = 0;
    char* s = expr;

    while (optop >= 0) {
        if (isdigit(*s)) {
            readn(&s, rpn, &rlen);
        } else if ((*s == '-' || *s == '+') && (s == expr ? 1 : (!isdigit(*(s - 1)) && *(s - 1) != ')'))) {
            // ��ͷ�ͳ���+-�ţ�����+-��֮ǰ��)���������������
            if (*s == '-') { // +�ź���
                rpn[rlen++] = *s;
            }
            s++;
        } else {
            Operator op = char2op(*s);
            Priority priority = cmp(sop[optop], op);
            switch (priority) {
            case Less:
                sop[++optop] = op;
                s++;
                break;
            case Equal:
                --optop;
                s++;
                break;
            case Greater:
            {
                Operator opcur = sop[optop--];
                rpn[rlen++] = op2char(opcur);
                rpn[rlen++] = ' ';
                break;
            }

            }
        }
    }
    if (rpn[rlen - 1] == ' ') { rlen--; }
    rpn[rlen] = '\0';
    puts(rpn);
}