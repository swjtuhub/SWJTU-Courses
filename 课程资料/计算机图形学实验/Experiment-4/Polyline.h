#pragma once
#include<windows.h>
#include <vector>
#include "Eigen/Dense"
#include "Variables.h"
#include "debug.h"
using namespace std;
using namespace Eigen;

// 多义线
struct Poly_line
{
    vector<POINT> points;
    RECT rect;
    static COLORREF color;
    Poly_line(){}
    Poly_line(vector<POINT> arr);
    
    void push_back(POINT t)
    { points.push_back(t); }
    size_t size()
    { return points.size();}
    bool contain_point(const POINT P) const;
    void Draw(HDC hdc, COLORREF color);
    void move(Point P);
    void scale(Matrix3f &T);
    void rotate(Matrix3f &T);
};

void Draw_Polyline(HWND hWnd, vector<POINT> &arr);