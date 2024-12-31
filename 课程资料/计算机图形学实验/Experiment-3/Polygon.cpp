#include "Polygon.h"
RECT polygon::rect={300,0,360,30};
COLORREF polygon::color=RGB(173,90,164);

bool polygon::contain_point(const POINT& P)
{
    int count = 0;
    int n = this->size();
    for (int i = 0, j = n - 1; i < n; j = i++) {
        if (((p[i].y > P.y) != (p[j].y > P.y)) &&
            (P.x < (p[j].x - p[i].x) * (P.y - p[i].y) / (p[j].y - p[i].y) + p[i].x)) {
            count++;
        }
    }
    return count%2==1;
}

void Draw_polygon(HWND hWnd, vector<POINT> &arr)
{
    HDC hdc=GetDC(hWnd);
    HPEN hPen=CreatePen(PS_SOLID,2,polygon::color);
    SelectObject(hdc,hPen);

    auto A=arr[0], B=arr[1];
    MoveToEx(hdc,A.x,A.y,nullptr);
    LineTo(hdc,B.x,B.y);
    arr.erase(arr.begin());
    DeleteObject(hPen);
    ReleaseDC(hWnd,hdc);
    if(polygons.back().size()==0)
        polygons.back().push_back(A);
    polygons.back().push_back(B);
}

// 最后一笔, 让多边形封闭
void polygon::Seal(HWND hWnd)
{
    HDC hdc=GetDC(hWnd);
    HPEN hPen=CreatePen(PS_SOLID,2,polygon::color);
    SelectObject(hdc,hPen);

    auto A=p.front() , B=p.back();
    MoveToEx(hdc,A.x,A.y,nullptr);
    LineTo(hdc,B.x,B.y);
    DeleteObject(hPen);
    ReleaseDC(hWnd,hdc);
    string str;
    for(int i=0;i<p.size();i++)
        str+="{"+to_string(p[i].x)+','+to_string(p[i].y)+"}, ";
    debug(str);
}