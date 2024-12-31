#pragma once
#include <windows.h>
#include <bits/stdc++.h>
#include "Point.h"
#include "Line.h"
#include "Variables.h"
#include "GeometryRelations.h"

// #define DEBUG
#include "debug.h"
using namespace std;
struct Circle
{
    POINT O;    // 圆心
    int r;      // 半径
    static RECT rect;
    static COLORREF color;
    Circle()
    {
        O={0,0};
        r=0;
    }
    Circle(POINT OO, int rr)
    {
        O=OO, r=rr;
    }
    bool contain_point(const POINT P)
    { return pow(P.x-O.x,2)+pow(P.y-O.y,2)<=r*r; }
};

void MidPoint_circle(HDC hdc, int xc, int yc, int radius, COLORREF color);
void Bresenham_circle(HDC hdc, int xc, int yc, int radius, COLORREF color);

void Draw_circle(HWND hWnd, vector<POINT> &arr);
