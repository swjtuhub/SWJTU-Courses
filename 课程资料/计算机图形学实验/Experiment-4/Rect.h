#pragma once
#include <windows.h>
#include <vector>
#include "Eigen/Dense"
#include "Variables.h"
#include "Fill_color.h"
using namespace std;
using namespace Eigen;
struct Rect
{
    POINT A,B;
    int left, right, bottom, top;
    bool is_filled; // 是否填充颜色
    RECT rect;
    static COLORREF color;
    Rect();
    Rect(POINT _A, POINT _B, bool _is_filled=false);
    Rect(int l, int t, int r, int b, bool _is_filled=false);
    
    bool contain_point(const POINT P) const
    { return left<=P.x && right>=P.x && top<=P.y && bottom>=P.y; }
    void Draw(HDC hdc, COLORREF color);
    void move(Point P);
    void scale(Matrix3f &T);
    void rotate(Matrix3f &T);
};

void Draw_rect(HWND hWnd, vector<POINT> &arr);