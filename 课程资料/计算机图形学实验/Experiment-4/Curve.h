#pragma once
#include <windows.h>
#include <bits/stdc++.h>
#include "Eigen/Dense"
#include "Variables.h"
using namespace std;
using namespace Eigen;

// 二次函数
struct Curve
{
    // double a,b,c;   // y=ax^2 + bx + c
    POINT A,B,C;
    RECT rect;
    static COLORREF color;
    Curve()
    { A=B=C={0,0}; }
    Curve(POINT _A, POINT _B, POINT _C);
    
    // y=fun(x)
    int fun(int x);
    bool contain_point(POINT P);
    void Draw(HDC hdc, COLORREF color);
    void move(Point P);
    void scale(Matrix3f &T);
    void rotate(Matrix3f &T);
};

void Draw_curve(HWND hWnd, vector<POINT> &arr);