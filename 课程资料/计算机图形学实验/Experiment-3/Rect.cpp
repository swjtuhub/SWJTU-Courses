#include "Rect.h"
RECT Rect::rect={120,0,180,30};
COLORREF Rect::color=RGB(148,255,51);

void Draw_rect(HWND hWnd, vector<POINT> &arr)
{
    HDC hdc=GetDC(hWnd);
    HPEN hPen=CreatePen(PS_SOLID,2,Rect::color);
    SelectObject(hdc,hPen);

    auto A=arr[0], B=arr[1];
    int l=min(A.x, B.x), r=A.x+B.x-l;       // left, right
    int b=min(A.y,B.y),  t=A.y+B.y-b;       // bottom, top
    arr.clear();

    // Rectangle(hdc,l,t,r,b);      // 实心矩形

    // 空心矩形
    MoveToEx(hdc,l,b,nullptr);      
    LineTo(hdc,l,t);
    LineTo(hdc,r,t);
    LineTo(hdc,r,b);
    LineTo(hdc,l,b);

    DeleteObject(hPen);
    ReleaseDC(hWnd,hdc);
    rects.emplace_back(l,r,b,t);
}