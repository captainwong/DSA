/*
https://pintia.cn/problem-sets/15/problems/827
7-20 表达式转换
分数 25
作者 DS课程组
单位 浙江大学
算术表达式有前缀表示法、中缀表示法和后缀表示法等形式。日常使用的算术表达式是采用中缀表示法，即二元运算符位于两个运算数中间。请设计程序将中缀表达式转换为后缀表达式。

输入格式:
输入在一行中给出不含空格的中缀表达式，可包含+、-、*、\以及左右括号()，表达式不超过20个字符。

输出格式:
在一行中输出转换后的后缀表达式，要求不同对象（运算数、运算符号）之间以空格分隔，但结尾不得有多余空格。

输入样例:
2+3*(7-4)+8/4
输出样例:
2 3 7 4 - * + 8 4 / +
代码长度限制16 KB
时间限制400 ms
内存限制64 MB
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
            // 开头就出现+-号，或者+-号之前是)以外的其他操作符
            if (*s == '-') { // +号忽略
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