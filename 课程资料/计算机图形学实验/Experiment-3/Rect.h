#pragma once
#include <windows.h>
#include <vector>
#include "Variables.h"
using namespace std;
struct Rect
{
    POINT A,B;
    int left, right, bottom, top;
    static RECT rect;
    static COLORREF color;
    Rect()
    {
        A=B={0,0};
        left=right=bottom=top=0;
    }
    Rect(int l, int r, int b, int t)
    {
        A={l,b}, B={r,t};
        left=l, right=r, bottom=b, top=t;
    }
    bool contain_point(const POINT P)
    { return left<=P.x && right>=P.x && bottom<=P.y && top>=P.y; }
};

void Draw_rect(HWND hWnd, vector<POINT> &arr);