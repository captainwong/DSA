#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<math.h>

#define PI 3.1415926


typedef struct Point {
    int x, y;
}Point;

typedef struct PointF {
    double x, y;
}PointF;

typedef struct Line {
    Point s, e;
}Line;

// ֱ��б��ʽ���� y=ax+b
typedef struct LineEquation {
    Line l;
    double a, b;
    int vertical;
}LineEquation;

typedef struct Rect {
    Point lt, rb;
}Rect;

typedef struct Circle {
    Point c;
    double r;
}Circle;

// �������
double distance(Point p, Point q)
{
    return sqrt((p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y));
}

// ���������
double squareOfTriangle(Point a, Point b, Point c)
{
    return fabs(a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)) / 2;
}

// ���������������ֱ��б��ʽ
LineEquation lineEquation(Line l)
{
    LineEquation equation = { l, 0.0, 0.0, 0 };
    if (l.s.x == l.e.x) {
        equation.vertical = 1;
    } else {
        equation.a = (l.s.y - l.e.y) * 1.0 / (l.s.x - l.e.x);
        equation.b = l.s.y - equation.a * l.s.x;
    }
    return equation;
}

// �㵽ֱ�ߵľ���
double distanceOfPointAndLine(Line line, Point p)
{
    double s = squareOfTriangle(line.s, line.e, p);
    double d = distance(line.s, line.e);
    double h = s * 2 / d;
    return h;
}

// ���������������ʽֱ�߷��̼���ֵ
int fPtByLine(Line line, Point p)
{
    // (y2-y1)(x2-x1) - (x-x1)(y2-y1) = 0
    Point A = line.s, B = line.e;
    return (p.y - A.y) * (B.x - A.x) - (p.x - A.x) * (B.y - A.y);
}

// ����ֱ����
int ptOnLine(Line line, Point p)
{
    // A,B,P���㹲�ߣ�AP �� AB == 0
    // AP = (P.x - A.x, P.y - A.y)
    // AB = (B.x - A.x, B.y - A.y)
    // V1 �� V2 = V1.x * V2.y - V1.y * V2.x �������
    // AP �� AB = (P.x - A.x) * (B.y - A.y) - (P.y - A.y) * (B.x - A.x)
    // �� (P.x - A.x) * (B.y - A.y) == (P.y - A.y) * (B.x - A.x)
    return (p.x - line.s.x) * (line.e.y - line.s.y) == (p.y - line.s.y) * (line.e.x - line.s.x);
}

// ����ֱ����
int ptfOnLine(Line line, PointF p)
{
    return (p.x - line.s.x) * (line.e.y - line.s.y) == (p.y - line.s.y) * (line.e.x - line.s.x);
}

// �����߶���
int ptOnSegment(Line seg, Point p)
{
    return ptOnLine(seg, p) && 
        ((p.x - seg.s.x) * (p.x - seg.e.x) <= 0) &&
        ((p.y - seg.s.y) * (p.y - seg.e.y) <= 0);
}

// �����߶���
int ptfOnSegment(Line seg, PointF p)
{
    return ptfOnLine(seg, p) &&
        ((p.x - seg.s.x) * (p.x - seg.e.x) <= 0) &&
        ((p.y - seg.s.y) * (p.y - seg.e.y) <= 0);
}

// ����Բ��
int ptOnCircle(Circle c, Point p)
{
    double d = distance(c.c, p);
    return d == c.r;
}

// ����Բ��
int ptInCircle(Circle c, Point p)
{
    double d = distance(c.c, p);
    return d < c.r;
}

// ���ھ�����
int ptOnRect(Rect r, Point p)
{
    return (p.x == r.lt.x && (r.rb.y <= p.y && p.y <= r.lt.y)) ||
        (p.y == r.lt.y && (r.lt.x <= p.x && p.x <= r.rb.x)) ||
        (p.x == r.rb.x && (r.rb.y <= p.y && p.y <= r.lt.y)) ||
        (p.y == r.rb.y && (r.lt.x <= p.x && p.x <= r.rb.x));
}

// ���ھ�����
int ptInRect(Rect r, Point p)
{
    return r.lt.x < p.x&& p.x < r.rb.x&&
        r.rb.y < p.y&& p.y < r.lt.y;
}

// ֱ��AB���߶�CD�Ƿ��ཻ
int lineSegmentIntersect(Line lineAB, Line segmentCD)
{    
    Point C = segmentCD.s, D = segmentCD.e;
    int fc = fPtByLine(lineAB, C);
    int fd = fPtByLine(lineAB, D);
    return fc * fd <= 0;
}

// �߶��Ƿ��ཻ
int segmentIntersect(Line seg1, Line seg2)
{
    return lineSegmentIntersect(seg1, seg2) && lineSegmentIntersect(seg2, seg1);
}

// �߶�ƽ�У��������ߣ�
int lineParallel(Line l1, Line l2)
{
    // ��ƽ����y��
    if (l1.s.x == l1.e.x && l2.s.x == l2.e.x)
        return 1;
    // ��ƽ����x��
    if (l1.s.y == l1.e.y && l2.s.y == l2.e.y)
        return 1;
    // б�����
    // (l1.e.y - l1.s.y) / (l1.e.x - l1.s.x) == (l2.e.y - l2.s.y) / (l2.e.x - l2.s.x)
    if ((l1.e.y - l1.s.y) * (l2.e.x - l2.s.x) == (l2.e.y - l2.s.y) * (l1.e.x - l1.s.x)) {
        return 1;
    }
    return 0;
}

// �߶ι���
int segmentColinear(Line l1, Line l2)
{
    Line l3 = { l1.s, l2.s };
    return lineParallel(l1, l2) && lineParallel(l1, l3);
}

// ֱ�߽���
// �޽��㷵��0������һ�����㷵��1����ֵP������1�����㷵��2
int lineIntersectionPoint(Line ab, Line cd, PointF* P)
{
    LineEquation eab = lineEquation(ab);
    LineEquation ecd = lineEquation(cd);
    if (eab.vertical && ecd.vertical) { // ����ֱ��б�ʶ�������
        if (ab.s.x == cd.s.x) {
            return 2;
        } else {
            return 0;
        }
    } else if (eab.vertical || ecd.vertical) { // ��һ��ֱ��б�ʲ�����
        LineEquation evert = eab.vertical ? eab : ecd;
        LineEquation enorm = eab.vertical ? ecd : eab;
        P->x = evert.l.s.x;
        P->y = enorm.a * P->x + enorm.b;
        return 1;
    } else { // ����ֱ��б�ʶ�����
        if (eab.a == ecd.a) { // ƽ��
            return 0;
        }
        // y = a1x + b1
        // y = a2x + b2
        // x = (b2-b1)/(a1-a2)
        // y = a1x + b1
        P->x = (ecd.b - eab.b) / (eab.a - ecd.a);
        P->y = eab.a * P->x + eab.b;
        return 1;
    }
}



// �߶ν���
// �޽��㷵��0������һ�����㷵��1����ֵP������1�����㷵��2
int segmentIntersectionPoint(Line ab, Line cd, PointF* P)
{
    LineEquation eab = lineEquation(ab);
    LineEquation ecd = lineEquation(cd);
    if (eab.vertical && ecd.vertical) { // ����ֱ��б�ʶ�������
        return 0;
        if (ab.s.x == cd.s.x) {
            return 2;
        } else {
            return 0;
        }
    } else if (eab.vertical || ecd.vertical) { // ��һ��ֱ��б�ʲ�����
        LineEquation evert = eab.vertical ? eab : ecd;
        LineEquation enorm = eab.vertical ? ecd : eab;
        P->x = evert.l.s.x;
        P->y = enorm.a * P->x + enorm.b;
        if (ptfOnSegment(ab, *P) && ptfOnSegment(cd, *P)) {
            return 1;
        }
    } else { // ����ֱ��б�ʶ�����
        if (eab.a == ecd.a) { // ƽ��
            return 0;
        }
        // y = a1x + b1
        // y = a2x + b2
        // x = (b2-b1)/(a1-a2)
        // y = a1x + b1
        P->x = (ecd.b - eab.b) / (eab.a - ecd.a);
        P->y = eab.a * P->x + eab.b; 
        if (ptfOnSegment(ab, *P) && ptfOnSegment(cd, *P)) {
            return 1;
        }
    }
    return 0;
}

// �������߶��Ƿ��ཻ���߶���������һ���ھ����ϻ�����ڼ���Ϊ�ཻ��
int lineRectIntersect(Rect r, Line l)
{
    if (ptOnRect(r, l.s) || ptInRect(r, l.s) || ptOnRect(r, l.e) || ptInRect(r, l.e)) {
        return 1;
    }

    Line ltrb = { r.lt, r.rb };
    Line lbrt = { {r.lt.x, r.rb.y}, {r.rb.x, r.lt.y} };
    if (segmentIntersect(l, ltrb) || segmentIntersect(l, lbrt)) {
        return 1;
    }

    return 0;
}

// �㵽���ε���̾���
double distanceOfPointAndRect(Rect r, Point p)
{
    if (ptInRect(r, p) || ptOnRect(r, p)) {
        return 0;
    }

    if (p.x < r.lt.x) {
        if (r.rb.y <= p.y && p.y <= r.lt.y) {
            return r.lt.x - p.x;
        } else if (p.y < r.rb.y) {
            Point lb = { r.lt.x, r.rb.y };
            return distance(lb, p);
        } else {
            return distance(r.lt, p);
        }
    } else if (p.x > r.rb.x) {
        if (r.rb.y <= p.y && p.y <= r.lt.y) {
            return p.x - r.rb.x;
        } else if (p.y < r.rb.y) {
            return distance(r.rb, p);
        } else {
            Point rt = { r.rb.x, r.lt.y };
            return distance(rt, p);
        }
    } else if (p.y > r.lt.y) {
        return p.y - r.lt.y;
    } else {
        return r.rb.y - p.y;
    }
}

int main()
{
    Line ab, cd;
    
    scanf("%d %d", &ab.s.x, &ab.s.y);
    scanf("%d %d", &ab.e.x, &ab.e.y);
    scanf("%d %d", &cd.s.x, &cd.s.y);
    scanf("%d %d", &cd.e.x, &cd.e.y);
    PointF p;
    if (segmentIntersectionPoint(ab, cd, &p) == 1) {
        printf("%.2lf %.2lf", p.x, p.y);
    } else {
        puts("-1");
    }
    return 0;
}
