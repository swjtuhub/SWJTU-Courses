#pragma once
#include<windows.h>
#include <vector>
#include <string>
#include "Eigen/Dense"
#include "Point.h"
#include "Variables.h"
#include "debug.h"
using std::vector;
using std::string;
using namespace Eigen;

// B 样条曲线
struct B_spline_curve
{
    vector<POINT> points;
    RECT rect;
    static COLORREF color;
    B_spline_curve(){}
    B_spline_curve(const vector<POINT> &control_points)
    {
        auto res=ComputeBSplineCurve(control_points);
        double l=res[0].x, r=res[0].x, b=res[0].y, t=res[0].y;
        for(auto P:res)
        {
            l=min(l,P.x), r=max(r,P.x);
            t=min(t,P.y), b=max(b,P.y);
            points.push_back(P.to_POINT());
        }
        rect={l,t,r,b};
    }
    vector<Point> ComputeBSplineCurve(const vector<POINT> &control_points);
    bool contain_point(const POINT P) const;
    void Draw(HDC hdc, COLORREF color);
    void move(Point P);
    void scale(Matrix3f &T);
    void rotate(Matrix3f &T);
};

void Draw_B_spline_curve(HWND hWnd, const vector<POINT> &control_points);