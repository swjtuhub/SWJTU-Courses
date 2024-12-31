#include "Rect.h"
COLORREF Rect::color=RGB(148,255,51);

Rect::Rect()
{
    A=B={0,0};
    left=right=bottom=top=0;
    is_filled = false;
}

Rect::Rect(POINT _A, POINT _B, bool _is_filled)
{
    A=_A, B=_B;
    left=min(A.x, B.x), right=max(A.x, B.x);
    top=min(A.y, B.y), bottom=max(A.y, B.y);
    rect={left,top,right,bottom};
    is_filled=_is_filled;
}

Rect::Rect(int l, int t, int r, int b, bool _is_filled)
{
    A={l,t}, B={r,b};
    is_filled=false;
    left=l, right=r, bottom=b, top=t;
    rect={left,top,right,bottom};
    is_filled=_is_filled;
}

void Rect::Draw(HDC hdc, COLORREF color)
{
    HPEN hPen=CreatePen(PS_SOLID,2,color);
    SelectObject(hdc,hPen);
    MoveToEx(hdc,left,top,nullptr);
    LineTo(hdc,right,top);
    LineTo(hdc,right,bottom);
    LineTo(hdc,left,bottom);
    LineTo(hdc,left,top);
    DeleteObject(hPen);
    if(is_filled)
        Scanline_fill_rect(hdc,*this);
}

void Rect::move(Point P)
{
    A=(Point(A)+P).to_POINT(), B=(Point(B)+P).to_POINT();
    *this=Rect(A,B,is_filled);
}

void Rect::scale(Matrix3f &T)
{
    Transform_point_by_matrix(A,T);
    Transform_point_by_matrix(B,T);
    *this=Rect(A,B,is_filled);
}

void Rect::rotate(Matrix3f &T)
{
    Transform_point_by_matrix(A,T);
    Transform_point_by_matrix(B,T);
    *this=Rect(A,B,is_filled);
}

void Draw_rect(HWND hWnd, vector<POINT> &arr)
{
    HDC hdc=GetDC(hWnd);
    auto A=arr[0], B=arr[1];
    int l=min(A.x, B.x), r=max(A.x,B.x);       // left, right
    int t=min(A.y,B.y),  b=max(A.y,B.y);       // top, bottom
    rects.emplace_back(l,t,r,b);
    rects.back().Draw(hdc,Rect::color);
    arr.clear();
    ReleaseDC(hWnd,hdc);
}