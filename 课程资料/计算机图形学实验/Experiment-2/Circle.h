#pragma once
#include <windows.h>
#include <bits/stdc++.h>
#include "Point.h"
#include "Line.h"
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
};

void Draw_circle(HWND hWnd, vector<POINT> &arr);
