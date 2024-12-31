#pragma once
#include<windows.h>
#include <vector>
#include "Variables.h"
#include "GeometryRelations.h"
using namespace std;
// 多边形
struct polygon
{
    vector<POINT> p;
    static RECT rect;
    static COLORREF color;
    polygon(){}
    polygon(vector<POINT> pp)
    { p=pp; }
    void push_back(POINT t)
    {
        p.push_back(t);
        return;
    }
    POINT& operator[](size_t index)
    { return p[index]; }
    const POINT& operator[](size_t index) const
    { return p[index]; }
    size_t size()
    { return p.size(); }
    bool contain_point(const POINT& P);
    void Seal(HWND hWnd); // 最后一笔, 让多边形封闭
};

void Draw_polygon(HWND hWnd, vector<POINT> &arr);

