#pragma once
#include<windows.h>
#include <vector>
#include "Variables.h"
#include "debug.h"
using namespace std;
// 多义线
struct Poly_line
{
    vector<POINT> p;
    static RECT rect;
    static COLORREF color;
    Polyline(){}
    Polyline(vector<POINT> pp)
    { p=pp; }
    void push_back(POINT t)
    {
        p.push_back(t);
        return;
    }
    size_t size()
    { return p.size();}
};

void Draw_Polyline(HWND hWnd, vector<POINT> &arr);