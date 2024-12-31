#pragma once
#include<windows.h>
#include<bits/stdc++.h>
#include<cmath>
#include<vector>
#include<string>
#include "Eigen/Dense"
#include "Point.h"
#include "State_macros.h"
#include "Variables.h"
#include "GeometryRelations.h"
#include "Graphics_transformation.h"
#include "debug.h"
using namespace std;
using namespace Eigen;

struct Point;
struct Line
{
    RECT rect;
    POINT s,e;
    double a,b,c;   // ax + by + c = 0
    static COLORREF color;
    Line()
    {
        a=b=c=0;
        s=e={0,0};
    }
    Line(POINT A, POINT B);
    Line(Point A, Point B);
    double length() const    // 长度 
    { return sqrt(pow(s.x-e.x,2)+pow(s.y-e.y,2)); }
    double slope() // 斜率
    { return double(e.y-s.y)/double(e.x-s.x); }
    bool contain_point(const POINT P) const 
    { return fabs((Point(P)-Point(s))^(Point(e)-Point(s)))/length() <= 3; }
    void Draw(HDC hdc, COLORREF color);
    void move(Point P);
    void scale(Matrix3f &T);
    void rotate(Matrix3f &T);
};

void Bresenham_Line(HDC hdc, POINT A, POINT B, COLORREF color);
void MidPoint_Line(HDC hdc, POINT A, POINT B, COLORREF color);

void Draw_line(HWND hWnd, vector<POINT> &arr, int state);

