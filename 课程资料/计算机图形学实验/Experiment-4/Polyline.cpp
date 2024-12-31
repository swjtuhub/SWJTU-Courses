#include "Polyline.h"
COLORREF Poly_line::color=RGB(136,15,255);

Poly_line::Poly_line(vector<POINT> arr)
{
    rect={arr[0].x,arr[0].y,arr[0].x,arr[0].y};
    for(auto P:arr)
        rect={min(rect.left,P.x),min(rect.top,P.y),max(rect.right,P.x),max(rect.bottom,P.y)};
}

bool Poly_line::contain_point(const POINT P) const
{
    for(int i=0;i<points.size()-1;i++)
        if(Line(points[i],points[i+1]).contain_point(P))
            return true;
    return false;
}

void Poly_line::Draw(HDC hdc, COLORREF color)
{
    HPEN hPen=CreatePen(PS_SOLID,2,color);
    SelectObject(hdc,hPen);
    MoveToEx(hdc,points[0].x,points[0].y,nullptr);
    for(int i=1;i<points.size();i++)
        LineTo(hdc,points[i].x,points[i].y);
    DeleteObject(hPen);
}

void Poly_line::move(Point P)
{
    for(auto &Q:points)
        Q=(Point(Q)+P).to_POINT();
    rect={rect.left+P.x,rect.top+P.y,rect.right+P.x,rect.bottom+P.y};
}

void Poly_line::scale(Matrix3f &T)
{
    for(auto &P:points)
        Transform_point_by_matrix(P,T);
    *this=Poly_line(points);
}

void Poly_line::rotate(Matrix3f &T)
{
    for(auto &P:points)
        Transform_point_by_matrix(P,T);
    *this=Poly_line(points);
}

void Draw_Polyline(HWND hWnd, vector<POINT> &arr)
{
    auto A=arr[0], B=arr[1];
    arr.erase(arr.begin());
    if(polylines.back().size()==0)
    {
        polylines.back().push_back(A);
        auto &rect=polylines.back().rect;
        rect={A.x,A.y,A.x,A.y};
    }
    polylines.back().push_back(B);
    auto &rect=polylines.back().rect;
    rect={min(rect.left,B.x),min(rect.top,B.y),max(rect.right,B.x),max(rect.bottom,B.y)};

    HDC hdc=GetDC(hWnd);
    Line(A,B).Draw(hdc,Poly_line::color);
    ReleaseDC(hWnd,hdc);
}