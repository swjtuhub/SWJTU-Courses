#pragma once
#include<windows.h>
#include <vector>
#include "Eigen/Dense"
#include "Variables.h"
#include "Fill_color.h"
#include "GeometryRelations.h"
using namespace std;
using namespace Eigen;

// 多边形
struct polygon
{
    vector<POINT> points;
    RECT rect;
    bool is_filled; // 是否填充颜色
    static COLORREF color;
    polygon(){ is_filled=false; }
    polygon(vector<POINT> _points, bool _is_filled=false)
    { points=_points, is_filled=_is_filled; }
    
    void push_back(POINT t)
    {
        points.push_back(t);
        return;
    }
    POINT& operator[](size_t index)
    { return points[index]; }
    const POINT& operator[](size_t index) const
    { return points[index]; }
    size_t size() const
    { return points.size(); }
    bool contain_point(const POINT P) const;
    void Seal(HWND hWnd); // 最后一笔, 让多边形封闭
    void Draw(HDC hdc, COLORREF color);
    void move(Point P);
    void scale(Matrix3f &T);
    void rotate(Matrix3f &T);
};

void Draw_polygon(HWND hWnd, vector<POINT> &arr);

