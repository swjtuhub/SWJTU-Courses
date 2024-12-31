#include "Curve.h"
RECT Curve::rect={180,0,240,30};
COLORREF Curve::color=RGB(23,205,255);

void Draw_curve(HWND hWnd, vector<POINT> &arr)
{
    HDC hdc=GetDC(hWnd);
    HPEN hPen=CreatePen(PS_SOLID,2,Curve::color);
    SelectObject(hdc,hPen);

    auto [x1,y1]=arr[0];
    auto [x2,y2]=arr[1];
    auto [x3,y3]=arr[2];
    auto fun=[&](double x)
    {
        double res=((x-x2)*(x-x3)/(x1-x2)/(x1-x3))*y1
                 + ((x-x1)*(x-x3)/(x2-x1)/(x2-x3))*y2
                 + ((x-x1)*(x-x2)/(x3-x1)/(x3-x2))*y3;
        return int(res+0.5);
    };

    int l=min({x1,x2,x3});
    int r=max({x1,x2,x3});
    MoveToEx(hdc,l,fun(l),nullptr);
    for(int x=l;x<=r;x++)
    {
        int y=fun(x);
        LineTo(hdc,x,y);
    }
    arr.clear();
    DeleteObject(hPen);
    ReleaseDC(hWnd,hdc);
    curves.emplace_back(arr[0],arr[1],arr[2]);
}