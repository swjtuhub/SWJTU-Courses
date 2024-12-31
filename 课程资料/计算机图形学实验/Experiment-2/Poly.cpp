#include "Poly.h"
extern vector<Poly> polylines;
RECT Poly::rect={240,0,300,30};
COLORREF Poly::color=RGB(136,15,255);

void Draw_Poly(HWND hWnd, vector<POINT> &arr)
{
    HDC hdc=GetDC(hWnd);
    HPEN hPen=CreatePen(PS_SOLID,2,Poly::color);
    SelectObject(hdc,hPen);

    auto A=arr[0], B=arr[1];
    MoveToEx(hdc,A.x,A.y,nullptr);
    LineTo(hdc,B.x,B.y);
    arr.erase(arr.begin());
    DeleteObject(hPen);
    ReleaseDC(hWnd,hdc);
    // polylines.emplace_back()     ??????
}