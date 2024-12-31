#pragma once
#include <windows.h>
#include <bits/stdc++.h>
using namespace std;

struct Point
{
    double x,y;
    Point(){x=y=0;}
    Point(double xx, double yy)
    {
        x=xx, y=yy;
    }
    Point(POINT P)
    {
        x=P.x, y=P.y;
    }
    POINT to_POINT()
    {
        int xx=x+0.5;
        int yy=y+0.5;
        return {xx,yy};
    }
};

bool operator<(const POINT &A, const POINT &B);

Point operator+(const Point &a, const Point &b);
Point operator-(const Point &a, const Point &b);
double operator^(const Point &a, const Point &b);   // 向量叉积
double operator*(const Point &a, const Point &b);   // 向量点积
Point operator*(const double &k, const Point &P);   // 向量数乘
Point operator/(const Point &P, const double &k);

double len(Point a, Point b);
