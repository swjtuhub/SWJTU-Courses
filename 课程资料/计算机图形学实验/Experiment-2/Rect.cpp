#include "Rect.h"
extern vector<Rect> rects;
RECT Rect::rect={120,0,180,30};
COLORREF Rect::color=RGB(148,255,51);

void Draw_rect(HWND hWnd, vector<POINT> &arr)
{
    HDC hdc=GetDC(hWnd);
    HBRUSH hBrush=CreateSolidBrush(Rect::color);
    SelectObject(hdc,hBrush);
    SetBkMode(hdc,TRANSPARENT);

    auto A=arr[0], B=arr[1];
    int l=min(A.x, B.x), r=A.x+B.x-l;
    int b=min(A.y,B.y),  t=A.y+B.y-b;
    Rectangle(hdc,l,t,r,b);
    arr.clear();
    DeleteObject(hBrush);
    ReleaseDC(hWnd,hdc);
    rects.emplace_back(l,r,b,t);
}