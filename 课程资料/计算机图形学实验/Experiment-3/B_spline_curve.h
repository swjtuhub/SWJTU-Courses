#pragma once
#include<windows.h>
#include <vector>
#include "Point.h"
#include "Variables.h"
#include "debug.h"
using std::vector;
// B 样条曲线
struct B_spline_curve
{
    vector<POINT> points;
    static RECT rect;
    static COLORREF color;
    B_spline_curve(){}
    B_spline_curve(const vector<POINT> &control_points)
    {
        auto res=ComputeBSplineCurve(arr);
        for(auto P:res)
            points.push_back(P.to_POINT());
    }
    vector<Point> ComputeBSplineCurve(const vector<POINT> &control_points);
};

void Draw_B_spline_curve(HWND hWnd);