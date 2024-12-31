#pragma once
#include <windows.h>
#include <bits/stdc++.h>
using namespace std;
// 二次函数
struct Curve
{
    POINT A,B,C;
    static RECT rect;
    static COLORREF color;
    Curve()
    {
        A=B=C={0,0};
    }
    Curve(POINT a, POINT b, POINT c)
    {
        A=a, B=b, C=c;
    }
};

void Draw_curve(HWND hWnd, vector<POINT> &arr);