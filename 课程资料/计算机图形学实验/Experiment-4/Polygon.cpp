#include "Polygon.h"
COLORREF polygon::color=RGB(173,90,164);

bool polygon::contain_point(const POINT P) const
{
    int count = 0;
    int n = points.size();
    for (int i = 0, j = n - 1; i < n; j = i++) {
        if (((points[i].y > P.y) != (points[j].y > P.y)) &&
            (P.x < (points[j].x - points[i].x) * (P.y - points[i].y) / (points[j].y - points[i].y) + points[i].x)) {
            count++;
        }
    }
    return count%2==1;
}

void polygon::Draw(HDC hdc, COLORREF color)
{
    HPEN hPen=CreatePen(PS_SOLID,2,color);
    SelectObject(hdc,hPen);
    MoveToEx(hdc,points[0].x,points[0].y,nullptr);
    for(int i=0;i<points.size();i++)
        LineTo(hdc,points[i].x,points[i].y);
    LineTo(hdc,points[0].x,points[0].y);
    DeleteObject(hPen);
    if(is_filled)
        Scanline_fill_polygon(hdc,*this);
}

void polygon::move(Point P)
{
    for(auto &Q:points)
        Q=(Point(Q)+P).to_POINT();
    rect={rect.left+P.x, rect.top+P.y, rect.right+P.x, rect.bottom+P.y};
}

void polygon::scale(Matrix3f &T)
{
    for(auto &P:points)
        Transform_point_by_matrix(P,T);
    *this=polygon(points);
}

void polygon::rotate(Matrix3f &T)
{
    for(auto &P:points)
        Transform_point_by_matrix(P,T);
    *this=polygon(points);
}

void Draw_polygon(HWND hWnd, vector<POINT> &arr)
{
    auto A=arr[0], B=arr[1];
    arr.erase(arr.begin());
    if(polygons.back().size()==0)
    {
        polygons.back().push_back(A);
        auto &rect=polygons.back().rect;
        rect={A.x,A.y,A.x,A.y};
    }
    polygons.back().push_back(B);
    auto &rect=polygons.back().rect;
    rect={min(rect.left,B.x),min(rect.top,B.y),max(rect.right,B.x),max(rect.bottom,B.y)};

    HDC hdc=GetDC(hWnd);
    Line(A,B).Draw(hdc,polygon::color);
    ReleaseDC(hWnd,hdc);
}

// 最后一笔, 让多边形封闭
void polygon::Seal(HWND hWnd)
{
    HDC hdc=GetDC(hWnd);
    auto A=points.front() , B=points.back();
    Line(A,B).Draw(hdc,polygon::color);
    ReleaseDC(hWnd,hdc);
    
    string str;
    for(int i=0;i<points.size();i++)
        str+="{"+to_string(points[i].x)+','+to_string(points[i].y)+"}, ";
    // debug(str);
}