#include "Point.h"

bool operator<(const POINT &A, const POINT &B)
{
    if(A.x != B.x)  return A.x<B.x;
    return A.y<B.y;
}

double len(Point a, Point b)
{
    return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));
}

Point operator+(const Point &a, const Point &b)
{
    return {a.x+b.x, a.y+b.y};
}

Point operator-(const Point &a, const Point &b)
{
    return {a.x-b.x, a.y-b.y};
}

// 向量叉积
double operator^(const Point &a, const Point &b)
{
    return a.x*b.y - a.y*b.x;
}


// 向量点积
double operator*(const Point &a, const Point &b)
{
    return a.x*b.x+a.y*b.y;
}

Point operator*(const double &k, const Point &P)
{
    return {P.x*k, P.y*k};
}

Point operator/(const Point &P, const double &k)
{
    return {double(P.x)/k, double(P.y)/k};
}

// 逆时针旋转 90 度
Point rotleft(Point P)
{
    return {-P.y,P.x};
}

// 顺时针旋转 90 度
Point rotright(Point P)
{
    return {P.y,-P.x};
}

// 化为长度为r的向量
Point trunc(Point P, double r)
{
    double l=len({0,0},P);
    if(fabs(l)<=1e-6)
        return P;
    r/=l;
    return {P.x*r, P.y*r};
}

Point lineprog(POINT P, Line A)
{
    return A.s + ( (((A.e-A.s)*(P-A.s)) * (A.e-A.s)) / (pow(len(A.e,A.s),2)) );
}