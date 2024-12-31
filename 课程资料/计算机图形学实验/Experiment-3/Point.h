#pragma once
#include <windows.h>
#include <bits/stdc++.h>
#include "Line.h"
using namespace std;

struct Line;
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
double operator^(const Point &a, const Point &b);
double operator*(const Point &a, const Point &b);
Point operator*(const double &k, const Point &P);
Point operator/(const Point &P, const double &k);
Point rotleft(Point P);
Point rotright(Point P);
Point trunc(Point P, double r);
// 求点P在直线A上的投影
Point lineprog(POINT P, Line A);

double len(Point a, Point b);
