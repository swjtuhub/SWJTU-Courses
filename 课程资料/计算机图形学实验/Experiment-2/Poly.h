#pragma once
#include<windows.h>
#include <vector>
using namespace std;
// 多义线
struct Poly
{
    vector<POINT> p;
    static RECT rect;
    static COLORREF color;
    Poly(){}
    Poly(vector<POINT> pp)
    {
        p=pp;
    }
};

void Draw_Poly(HWND hWnd, vector<POINT> &arr);