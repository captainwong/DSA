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

// 直线斜截式方程 y=ax+b
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

// 两点距离
double distance(Point p, Point q)
{
    return sqrt((p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y));
}

// 三角形面积
double squareOfTriangle(Point a, Point b, Point c)
{
    return fabs(a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)) / 2;
}

// 根据两点坐标计算直线斜截式
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

// 点到直线的距离
double distanceOfPointAndLine(Line line, Point p)
{
    double s = squareOfTriangle(line.s, line.e, p);
    double d = distance(line.s, line.e);
    double h = s * 2 / d;
    return h;
}

// 将点坐标带入两点式直线方程计算值
int fPtByLine(Line line, Point p)
{
    // (y2-y1)(x2-x1) - (x-x1)(y2-y1) = 0
    Point A = line.s, B = line.e;
    return (p.y - A.y) * (B.x - A.x) - (p.x - A.x) * (B.y - A.y);
}

// 点在直线上
int ptOnLine(Line line, Point p)
{
    // A,B,P三点共线：AP · AB == 0
    // AP = (P.x - A.x, P.y - A.y)
    // AB = (B.x - A.x, B.y - A.y)
    // V1 · V2 = V1.x * V2.y - V1.y * V2.x 向量叉乘
    // AP · AB = (P.x - A.x) * (B.y - A.y) - (P.y - A.y) * (B.x - A.x)
    // 即 (P.x - A.x) * (B.y - A.y) == (P.y - A.y) * (B.x - A.x)
    return (p.x - line.s.x) * (line.e.y - line.s.y) == (p.y - line.s.y) * (line.e.x - line.s.x);
}

// 点在直线上
int ptfOnLine(Line line, PointF p)
{
    return (p.x - line.s.x) * (line.e.y - line.s.y) == (p.y - line.s.y) * (line.e.x - line.s.x);
}

// 点在线段上
int ptOnSegment(Line seg, Point p)
{
    return ptOnLine(seg, p) && 
        ((p.x - seg.s.x) * (p.x - seg.e.x) <= 0) &&
        ((p.y - seg.s.y) * (p.y - seg.e.y) <= 0);
}

// 点在线段上
int ptfOnSegment(Line seg, PointF p)
{
    return ptfOnLine(seg, p) &&
        ((p.x - seg.s.x) * (p.x - seg.e.x) <= 0) &&
        ((p.y - seg.s.y) * (p.y - seg.e.y) <= 0);
}

// 点在圆上
int ptOnCircle(Circle c, Point p)
{
    double d = distance(c.c, p);
    return d == c.r;
}

// 点在圆内
int ptInCircle(Circle c, Point p)
{
    double d = distance(c.c, p);
    return d < c.r;
}

// 点在矩形上
int ptOnRect(Rect r, Point p)
{
    return (p.x == r.lt.x && (r.rb.y <= p.y && p.y <= r.lt.y)) ||
        (p.y == r.lt.y && (r.lt.x <= p.x && p.x <= r.rb.x)) ||
        (p.x == r.rb.x && (r.rb.y <= p.y && p.y <= r.lt.y)) ||
        (p.y == r.rb.y && (r.lt.x <= p.x && p.x <= r.rb.x));
}

// 点在矩形内
int ptInRect(Rect r, Point p)
{
    return r.lt.x < p.x&& p.x < r.rb.x&&
        r.rb.y < p.y&& p.y < r.lt.y;
}

// 直线AB与线段CD是否相交
int lineSegmentIntersect(Line lineAB, Line segmentCD)
{    
    Point C = segmentCD.s, D = segmentCD.e;
    int fc = fPtByLine(lineAB, C);
    int fd = fPtByLine(lineAB, D);
    return fc * fd <= 0;
}

// 线段是否相交
int segmentIntersect(Line seg1, Line seg2)
{
    return lineSegmentIntersect(seg1, seg2) && lineSegmentIntersect(seg2, seg1);
}

// 线段平行（包含共线）
int lineParallel(Line l1, Line l2)
{
    // 都平行于y轴
    if (l1.s.x == l1.e.x && l2.s.x == l2.e.x)
        return 1;
    // 都平行于x轴
    if (l1.s.y == l1.e.y && l2.s.y == l2.e.y)
        return 1;
    // 斜率相等
    // (l1.e.y - l1.s.y) / (l1.e.x - l1.s.x) == (l2.e.y - l2.s.y) / (l2.e.x - l2.s.x)
    if ((l1.e.y - l1.s.y) * (l2.e.x - l2.s.x) == (l2.e.y - l2.s.y) * (l1.e.x - l1.s.x)) {
        return 1;
    }
    return 0;
}

// 线段共线
int segmentColinear(Line l1, Line l2)
{
    Line l3 = { l1.s, l2.s };
    return lineParallel(l1, l2) && lineParallel(l1, l3);
}

// 直线交点
// 无交点返回0，仅有一个交点返回1并赋值P，多于1个交点返回2
int lineIntersectionPoint(Line ab, Line cd, PointF* P)
{
    LineEquation eab = lineEquation(ab);
    LineEquation ecd = lineEquation(cd);
    if (eab.vertical && ecd.vertical) { // 两条直线斜率都不存在
        if (ab.s.x == cd.s.x) {
            return 2;
        } else {
            return 0;
        }
    } else if (eab.vertical || ecd.vertical) { // 有一条直线斜率不存在
        LineEquation evert = eab.vertical ? eab : ecd;
        LineEquation enorm = eab.vertical ? ecd : eab;
        P->x = evert.l.s.x;
        P->y = enorm.a * P->x + enorm.b;
        return 1;
    } else { // 两条直线斜率都存在
        if (eab.a == ecd.a) { // 平行
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



// 线段交点
// 无交点返回0，仅有一个交点返回1并赋值P，多于1个交点返回2
int segmentIntersectionPoint(Line ab, Line cd, PointF* P)
{
    LineEquation eab = lineEquation(ab);
    LineEquation ecd = lineEquation(cd);
    if (eab.vertical && ecd.vertical) { // 两条直线斜率都不存在
        return 0;
        if (ab.s.x == cd.s.x) {
            return 2;
        } else {
            return 0;
        }
    } else if (eab.vertical || ecd.vertical) { // 有一条直线斜率不存在
        LineEquation evert = eab.vertical ? eab : ecd;
        LineEquation enorm = eab.vertical ? ecd : eab;
        P->x = evert.l.s.x;
        P->y = enorm.a * P->x + enorm.b;
        if (ptfOnSegment(ab, *P) && ptfOnSegment(cd, *P)) {
            return 1;
        }
    } else { // 两条直线斜率都存在
        if (eab.a == ecd.a) { // 平行
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

// 矩形与线段是否相交（线段上有任意一点在矩形上或矩形内即认为相交）
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

// 点到矩形的最短距离
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
