#pragma once
#include <windows.h>
#include <bits/stdc++.h>
#include "Eigen/Dense"
#include "Point.h"
#include "Line.h"
#include "Fill_color.h"
#include "Variables.h"
#include "GeometryRelations.h"
#include "debug.h"
using namespace std;
using namespace Eigen;
struct Circle
{
    POINT O;    // 圆心
    int r;      // 半径
    bool is_filled; // 是否填充颜色
    RECT rect;
    static COLORREF color;
    Circle()
    {
        O={0,0};
        r=0;
        is_filled = false;
    }
    Circle(POINT OO, int rr, bool _is_filled=false)
    { O=OO, r=rr, is_filled=_is_filled, rect={O.x-r,O.y-r,O.x+r,O.y+r}; }
    bool contain_point(const POINT P) const
    { return pow(P.x-O.x,2)+pow(P.y-O.y,2)<=r*r; }
    void Draw(HDC hdc, COLORREF color);
    void move(Point P);
    void scale(Matrix3f &T);
    void rotate(Matrix3f &T);
};

void MidPoint_circle(HDC hdc, int xc, int yc, int radius, COLORREF color);
void Bresenham_circle(HDC hdc, int xc, int yc, int radius, COLORREF color);

void Draw_circle(HWND hWnd, vector<POINT> &arr);
